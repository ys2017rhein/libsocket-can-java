# RevolutionPi libsocket CAN JNI wrapper

Simple JNI wrapper to access the Kunbus RevolutionPi CAN hardware from within Java  

## Getting Started

These instructions will get you a copy of the project on your rev pi and build the library on that controller.

## Built Instructions

* login to your RevolutionPi and install git tools
* git clone [https://github.com/clehne/libsocket-can-java](https://github.com/clehne/libsocket-can-java)
* cd libsocket-can-java  
* make clean
* make all
* make check

## Deployment

Use the resulting library [./dist/libsocket-can-java.jar](./dist/libsocket-can-java.jar) for your needs.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Contributing

* The project is a fork and an almost 100% copy of [entropia - libsocket-can-java.git](https://github.com/entropia/libsocket-can-java.git)
* only minor adoptions to be part of the great and inspiring [openems](https://openems.io/) project. 

## Authors

* **waal70** - *initial* - 
* **entropia** - *adoptions, CAN filter,...* - 
* **C. Lehne** - *minor changes, mainly for buildprocess *


## Acknowledgments

* Hat tip to anyone whose code was used
