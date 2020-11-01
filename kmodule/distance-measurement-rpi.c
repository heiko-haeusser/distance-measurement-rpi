#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/hrtimer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Heiko Haeusser");
MODULE_DESCRIPTION("Linux Course Task 6");
MODULE_VERSION("1.0");

#define INTERVAL_US (1 * 1000LL) //100ms (scaled in ns)
#define INTERVAL_MS (1 * 1000000LL) //100ms (scaled in ns)
#define DISTANCE_FACTOR 10000000 * 343 //strip down the calculation to a minimum
                                       //let the compiler calculate this, it can do it better 

//GPIO definitions---------------------------
static unsigned int gpioLED = 23;
static unsigned int gpioBtn = 26;
static unsigned int gpioPuBtn = 13;
static unsigned int gpioTrig = 18;
static unsigned int gpioEcho = 24;

//IRQ definitions---------------------------
static unsigned int irqNumberBtn = -1;
static unsigned int irqNumberEcho = -1;

//HRTIMER definitions-----------------------
static enum hrtimer_restart procMeasurement(struct hrtimer*);
static struct hrtimer htimer;
static ktime_t ktime_interval;

//Helper variables for PDC functionality----
static int state = 0;
static int stateEval = 0;
static unsigned long  start_ts = 0; //set when rising edge detected
static unsigned long  stop_ts = 0; //set when falling edge detected
static unsigned long duration = 0;
static unsigned int distanceCm = 0;

//Callback declarations---------------------
static irq_handler_t btn_irq_handler(unsigned int irq, void* dev_id, struct pt_regs* regs);
static irq_handler_t echo_irq_handler(unsigned int irq, void* dev_id, struct pt_regs* regs);

static int init_gpios(void) 
{
   int res = 0; //temporary variable to store the request IRQ result

   // ######################## Setup GPIO setup start ###########################
   // Set the pullup for the button to 1-----------------------------------
   gpio_request(gpioPuBtn, "sysfs");
   gpio_direction_output(gpioPuBtn, 1);
   gpio_export(gpioPuBtn, false);     

   // Setup the button-----------------------------------------------------
   gpio_request(gpioBtn, "sysfs");
   gpio_direction_input(gpioBtn);
   gpio_set_debounce(gpioBtn, 200); 
   gpio_export(gpioBtn, false);

   // setup the IRQ for the button
   irqNumberBtn = gpio_to_irq(gpioBtn);
   printk(KERN_ALERT "The button is mapped to IRQ: %d\n", irqNumberBtn);
      
   res = request_irq(irqNumberBtn,
                        (irq_handler_t) btn_irq_handler,
                        IRQF_TRIGGER_RISING,
                        "btn_gpio_handler", // Used in /proc/interrupts as id
                        NULL);

   printk(KERN_ALERT "The interrupt request result is: %d\n", res);

   // Setup the LED---------------------------------------------------------
   gpio_request(gpioLED, "sysfs");
   gpio_direction_output(gpioLED, 0); 
   gpio_export(gpioLED, false);   

   // Setup the trigger pin-------------------------------------------------
   gpio_request(gpioTrig, "sysfs");
   gpio_direction_output(gpioTrig, 0); 
   gpio_export(gpioTrig, false);   

   // Setup the echo pin----------------------------------------------------
   gpio_request(gpioEcho, "sysfs");
   gpio_direction_input(gpioEcho);
   gpio_export(gpioEcho, false);

   // setup the IRQ for the echo
   irqNumberEcho = gpio_to_irq(gpioEcho);
   printk(KERN_ALERT "The echo is mapped to IRQ: %d\n", irqNumberEcho);
      
   res = request_irq(irqNumberEcho,
                        (irq_handler_t) echo_irq_handler,
                        IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
                        "echo_gpio_handler", // Used in /proc/interrupts as id
                        NULL);

   printk(KERN_ALERT "The interrupt request result is: %d\n", res);

   // ######################## Setup GPIO setup end ###########################
   printk(KERN_ALERT "\n\n---------- initialization of GPIO finished ----------\n\n");

   return res;
}

static int __init rpi_dist_init(void)
{
   int res = 0; //temporary variable

   printk(KERN_ALERT "\n\n----------Task 6 Kernel Module started----------\n\n");

   res = init_gpios(); //temporary variable to store the gpio init result
   
   ktime_interval = ktime_set(0, 500*INTERVAL_MS);//seconds,nanoseconds
   hrtimer_init (& htimer, CLOCK_REALTIME, HRTIMER_MODE_REL);
   htimer.function = procMeasurement;
   hrtimer_start(& htimer, ktime_interval, HRTIMER_MODE_REL);

/*
   //only for testing purpose of echo IRQ
   // msleep(1);
   // gpio_set_value(gpioTrig,1);
   // msleep(1);   
   // gpio_set_value(gpioTrig, 0);
*/
   return res;
}

static void __exit rpi_dist_exit(void)
{
   int ret = 0;
   ret = hrtimer_cancel( &htimer);
   if (ret) {
      printk("mod_hrtimer: The timer was still in use...\n");
      printk("mod_hrtimer: HR Timer module uninstalling\n");
   }

   gpio_set_value(gpioLED, 0);
   gpio_unexport(gpioLED);

   gpio_set_value(gpioPuBtn, 0);
   gpio_unexport(gpioPuBtn);

   free_irq(irqNumberBtn, NULL);
   gpio_unexport(gpioBtn);

   gpio_set_value(gpioTrig, 0);
   gpio_unexport(gpioTrig);

   free_irq(irqNumberEcho, NULL);
   gpio_unexport(gpioEcho);

   gpio_free(gpioLED);
   gpio_free(gpioPuBtn);
   gpio_free(gpioBtn);
   gpio_free(gpioTrig);
   gpio_free(gpioEcho);

   destroy_hrtimer_on_stack(&htimer);

   printk(KERN_ALERT "\n\n----------Task 6 Kernel Module ended----------\n\n");
}

/*
 * This function interrupt handler that is attached to the button GPIO.
 */
static irq_handler_t btn_irq_handler(unsigned int irq, void* dev_id, struct pt_regs* regs)
{
	printk(KERN_ALERT "Interrupt, BUTTON state is %d\n", gpio_get_value(gpioBtn));
   //rpi_dist_exit(); here it was planned to stop the kernel module, but invoking the exit function is not a good idea.. :D
   return (irq_handler_t) IRQ_HANDLED; // Announce that the IRQ has been handled correctly
}

static void printPdcStatus(void)
{
   duration = stop_ts-start_ts;
   distanceCm = (duration/2);
   distanceCm = distanceCm / 343;
   distanceCm = distanceCm / 100;
   
   // printk(KERN_ALERT "duration: %lu \t start:%lu \t stop:%lu\n", duration, start_ts, stop_ts);

   if (distanceCm < 30) {
		printk(KERN_ALERT "STOP:\t\t distance is %dcm \t %d,%dm\n", distanceCm, distanceCm/100,distanceCm-(distanceCm/100));
	} else if (distanceCm <= 100) {
      printk(KERN_ALERT "WARNING:\t\t distance is %dcm \t %d,%dm\n", distanceCm, distanceCm/100,distanceCm-(distanceCm/100));
	} else if (distanceCm < 300) { //exclude wrong measurments
      printk(KERN_ALERT "OK:\t\t distance is %dcm \t %d,%dm\n", distanceCm, distanceCm/100,distanceCm-(distanceCm/100));
	}
}

static irq_handler_t echo_irq_handler(unsigned int irq, void* dev_id, struct pt_regs* regs)
{
   // printk(KERN_ALERT "Interrupt, ECHO pin state is %d\n", gpio_get_value(gpioEcho));

   if(gpio_get_value(gpioEcho)==1) {
      start_ts = (unsigned long) ktime_get_ns();
      stateEval = 1;
   } else if(stateEval==1) {
      stop_ts = (unsigned long) ktime_get_ns();      
      printPdcStatus(); //print the result
      stateEval = 0; //reset the evaluation state for the next measurement
   } else {
      stateEval = 0; //reset the evaluation state for two falling edges to ignore the measurement
      printk(KERN_ALERT "ignore this interrupt, because rising edge is missing\n");
   }
   
   return (irq_handler_t) IRQ_HANDLED; // Announce that the IRQ has been handled correctly
}

static enum hrtimer_restart procMeasurement(struct hrtimer *unused) {
	switch (state) {
	case 0:
		state = 1;
		gpio_set_value(gpioLED, 1);
		gpio_set_value(gpioTrig, 1);
		ktime_interval = ktime_set(0, 20 * INTERVAL_US); //switch trigger pin off after 20us
		// printk(KERN_ALERT "----------Trigger set ----------\n");
		break;
	case 1:
		state = 2;
		gpio_set_value(gpioTrig, 0);
      ktime_interval = ktime_set(0, 50 * INTERVAL_MS); //switch LED off after 50ms
		// printk(KERN_ALERT "----------Trigger cleared ----------\n");
		break;
	case 2:
		state = 0;
		gpio_set_value(gpioLED, 0);
		ktime_interval = ktime_set(0, 450 * INTERVAL_MS); //trigger new measurement after 500ms (450+50 from LED)
		// printk(KERN_ALERT "----------LED cleared ----------\n");
		break;
	default:
   	printk(KERN_ALERT "\n\n----------this should never be excecuted..----------n\n");

		break;
	}
	hrtimer_forward_now(&htimer, ktime_interval);
	return HRTIMER_RESTART;
}

module_init(rpi_dist_init);
module_exit(rpi_dist_exit);
