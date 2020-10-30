# distance-measurement-rpi

[![Contributors][contributors-shield]][contributors-url]
[![GNU License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/heiko-haeusser/linux_course">
    <img src="images/logo.jpg" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">RPI4 Project Ultrasonic Sensor Board V1.1</h3>

  <p align="center">
    Hardware Related CPP course - week 4 final Projekt
    <br />
    <a href="https://github.com/heiko-haeusser/linux_course"><strong>Explore the docs »</strong></a>
    <br />
    <br />
  </p>
</p>

<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
* [Installation](#installation)
* [Usage](#usage)
* [Roadmap](#roadmap)
* [License](#license)
* [Contact](#contact)
* [Acknowledgements](#acknowledgements)



<!-- ABOUT THE PROJECT -->
## About The Project

<img src="images/logo.jpg" alt="Logo" width="380" height="380">

The aim of the project is the development of a distance measurement for a RPI custom board with LED, Button and Ultrasonic Sensor.
The given code supports custom board version V1.1<br /><br />

The Board has the following IO configuration:<br />
_Button 	GPIO26_<br />
_LED 		GPIO2_<br />
_Ultrasonic Sensor_<br />
_Trigger	GPIO18_<br />
_Echo		GPIO24_<br />

### The project can be separated in the following main tasks:
1. Development of a Custom Kernel module that interfaces a distance sensor (last task)<br />
2. C++ Application to access sensor data and control status LED (first task)<br />
3. Custom logging with temporary storage<br />

### Additional goals are:
4. Simple system setup using shell script for deployment (side task)<br />
5. Project setup with installation from external drive (e.g. USB stick) in mind<br />

## Installation

1. Clone the repo
```sh
git clone https://github.com/heiko-haeusser/linux_course.git
```

2. run install script (install.sh)<br />
parameters: [-shell] [-cpp]<br />
  -shell: installs the solution from task 2 <br />
  -cpp: installs the solution as cpp solution (not yet implemented)<br />
```sh
sudo ./install.sh
```

<!-- USAGE EXAMPLES -->
## Usage

short _how-to_ goes here in the future

<!-- ROADMAP -->
## Roadmap

Task description:<br />
### Task 1. Setup of a git repo with this readme file
#### Task 1a: Prepare already an install script. Makes life easier..(install script, will be adjusted during development)
Development of a install script which automatically deploys all necessary sources to the specified locations<br />

  #### a) parameters: [-shell] [-cpp]<br />
  -shell: installs the solution from task 2 <br />
  -cpp: installs the solution as cpp solution (not yet implemented)<br />

### 1.b Project setup with installation from external drive (e.g. USB stick) in mind
not clear what needs to be done here
### Task 2. Shell Script Application to access GPIO and control status LED
Task description: Write a simple shell script that sets up GPIO23 (the LED) as output and let it blink twice with a cycle time of 1s.

### Task 3. C++ Application to access sensor data, control status LED and perform measurement
3a. Write a simple C++ application that compiles and runs on the target hardware.
3b. An implementation with object-oriented architecture that is able to read values from GPIO,
forward them to a processing component for the runtime calculations and blink the LED according
to a classification based on the distance of an object (1 s interval OK, 300 ms interval
Warning, 20 ms interval Stop). There shall be one measurement every 500 ms. The result of a
successful distance measurement shall be printed on standard output.

### Task 4: Systemd service unit
Write a service unit that starts the PDC C++ application at boot time (target multi-user).

### Task 5: Logging & logging filesystem
Write a timer unit that runs a script that writes current RAM and CPU usage every 5s into
a file stored on a tmpfs.

### Task 6: Custom kernel module
Write a simple kernel module that can be loaded. Implement the distance measurement
from Task 3 as part of this module with an interval of 500 ms. Between each measurement
the connected LED shall flash for 50 ms. For test purposes the measured distance
shall be printed to the kernel log.



<!-- LICENSE -->
## License

Distributed under the GPLv3 License. See [LICENSE](https://github.com/heiko-haeusser/linux_course/blob/main/LICENSE) for more information.


<!-- CONTACT -->
## Contact

Heiko Haeusser - heiko.haeusser@web.de

Project Link: [https://github.com/heiko-haeusser/linux_course](https://github.com/heiko-haeusser/linux_course)



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/heiko-haeusser/repo.svg?style=flat-square
[contributors-url]: https://github.com/heiko-haeusser/repo/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/heiko-haeusser/repo.svg?style=flat-square
[forks-url]: https://github.com/heiko-haeusser/repo/network/members
[stars-shield]: https://img.shields.io/github/stars/heiko-haeusser/repo.svg?style=flat-square
[stars-url]: https://github.com/heiko-haeusser/repo/stargazers
[issues-shield]: https://img.shields.io/github/issues/heiko-haeusser/repo.svg?style=flat-square
[issues-url]: https://github.com/heiko-haeusser/repo/issues
[license-shield]: https://img.shields.io/github/license/heiko-haeusser/repo.svg?style=flat-square
[license-url]: https://github.com/heiko-haeusser/linux_course/blob/main/LICENSE
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/heiko-haeusser
