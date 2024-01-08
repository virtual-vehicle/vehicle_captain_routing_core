# vehicleCAPTAIN - routing core
This software fixes the issue of multiple available hardware and software components for V2X communication.
![vehicleCAPTAIN Demo Board - Closed](res/figures/21_platform_design.drawio.png "High Level Architecture (HLA) of the vehicleCAPTAIN routing core")

The available implementation supports ITSG5 (802.11p) communication via the [Unex SOM301-E](https://unex.com.tw/en/product/som/), as well as V2N via an MQTT server.

Checkout the documentation folder for Charts, Configurations and Setups. 

## IMPORTANT Prerequisites for Quickstart
The [Unex V2XCast](https://unex.com.tw/en/v2xcast/) library is a mandatory core component of this software. The software will not compile without it. Please simply add the software in the respictive dummy folders and remove the "dummy" part. Then continue with.

```bash
echo "IMPORTANT: replace 'SDK*-dummy' folders with Unex V2XCast SDK"
make base
make local
```

## Features
This software handles the input and output of V2X ASN1 streams. If a specific interface is implemented, it can be used for sending and receiving. The user interface does not change.

**Advantage**: one interface for all, i.e. the user interface is hardware independent

**Disadvantage**: if you need just one V2X HW implementation, this may be too much overhead for you.

In any case, you may also have a look at our [other tools](https://github.com/virtual-vehicle/vehicle_captain).

## Documentation
Please find the documentation in the doc folder. It contains flowcharts and class diagrams.

## Copyright
Please cite the [vehicleCAPTAIN paper](https://github.com/virtual-vehicle/vehicle_captain_toolbox/blob/main/LITERATURE.md) if you used any part of this software toolbox for your work.

## Contribution Guidelines
Feel free to add fixes and new features.

## Authors
Main Author [Christoph Pilz](https://github.com/MrMushroom).

## Acknowledgement
The majority of this work is part of my ([Christoph Pilz](https://www.researchgate.net/profile/Christoph-Pilz)) PhD studies at [Graz University of Technology](https://www.tugraz.at/home) in cooperation with the [Virtual Vehicle Research GmbH](https://www.v2c2.at/). Features are integrated across various projects.

Contributions to the vehicleCAPTAIN are receiving funding as listed on the [main page](https://github.com/virtual-vehicle/vehicle_captain).
