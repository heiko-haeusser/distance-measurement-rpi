#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Heiko Haeusser");
MODULE_DESCRIPTION("Linux Course Task 6");
MODULE_VERSION("1.0");

#define INTERVAL_US (1 * 1000LL) //100ms (scaled in ns)
#define INTERVAL_MS (1 * 1000000LL) //100ms (scaled in ns)

static unsigned int gpioLED = 23;
static unsigned int gpioBtn = 26;
static unsigned int gpioPuBtn = 13;
static unsigned int gpioTrig = 18;
static unsigned int gpioEcho = 24;


static unsigned int irqNumberBtn = -1;
static unsigned int irqNumberEcho = -1;

static int state = 0;
// static int stateEval = 0;

static bool ledOn = 0;

static irq_handler_t btn_irq_handler(unsigned int irq,
                                         void* dev_id,
                                         struct pt_regs* regs);

static int __init rpi_dist_init(void)
{
   int res = 0; //temporary variable to store the request IRQ result

   // Set the pullup for the button to 1
   gpio_request(gpioPuBtn, "sysfs");
   gpio_direction_output(gpioPuBtn, 1);
   gpio_export(gpioPuBtn, false);     

   // Setup the button
   gpio_request(gpioBtn, "sysfs");
   gpio_direction_input(gpioBtn);
   gpio_set_debounce(gpioBtn, 200); 
   gpio_export(gpioBtn, false);

   // setup the IRQ for the button
   irqNumberBtn = gpio_to_irq(gpioBtn);
   printk(KERN_ALERT "The button is mapped to IRQ: %d\n", irqNumberBtn);
      
   res = request_irq(irqNumberBtn,
                        (irq_handler_t) btn_irq_handler,
                        IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
                        "my_gpio_handler", // Used in /proc/interrupts as id
                        NULL);

   printk(KERN_ALERT "The interrupt request result is: %d\n", res);

   // Setup the LED
   ledOn = true;
   gpio_request(gpioLED, "sysfs");
   gpio_direction_output(gpioLED, 0); 
   gpio_export(gpioLED, false);   
   
   return res;
}

static void __exit rpi_dist_exit(void)
{
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
}

/*
 * This function interrupt handler that is attached to the button GPIO.
 */
static irq_handler_t btn_irq_handler(unsigned int irq, void* dev_id, struct pt_regs* regs)
{
   printk(KERN_ALERT "Interrupt, button state is %d\n", gpio_get_value(gpioBtn));
   return (irq_handler_t) IRQ_HANDLED; // Announce that the IRQ has been handled correctly
}

module_init(rpi_dist_init);
module_exit(rpi_dist_exit);
