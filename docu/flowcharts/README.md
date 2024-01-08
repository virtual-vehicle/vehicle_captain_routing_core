# Flowcharts

This Readme contains information on the flowcharts about the unex upgrade of the routing platform.
Information about V2X and about the routing platform are within the confluence documents.

## Threading Architecture Overview

### Interface Threads
Every single interface has its own set of threads: one for input and one for output.

### Communication Control Threads:
The Communication Control has its own seperate set of threads: an input and an output thread.
The input thread of the Communication Control aggregates or collects the inputs from all the interfaces' input threads.
The output thread of the Communication Control dispatches or sends messages out to the correct interface's output threads.
The output thread oversees the entire operation of the communication Control. 
While the communication control's input and output threads handle the actual message flow,
cc thread ensures the proper functioning of the entire communication control.

### V2X Routing Middleware Thread:
The rc thread is responsible for message routing. 
