# Configuring the Routing Core
This software does not have a config file yet. Configuration has to be done in code.

## Important Settings
Important settings are explained below.

### Setting the Debug Level
You may configure the debug level *main.cpp*. Most debug levels are set recursively

### Adding new Interfaces
This is a two step process:
1. add an interface within *v2x_interface_control* for your interface
2. initialize this interface in *CommunicationControl.cpp*

## Contribution
Please feel free to contribute features and fixes!\
-> i.e. new interfaces, behavior, or simple bug fixes
