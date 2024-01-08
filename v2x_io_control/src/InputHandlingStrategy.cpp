// -*- lsst-c++ -*-

/*
* VIF V2X Platform
* See COPYRIGHT file at the top of the source tree.
*
* This product includes software developed by the
* InSecTT Project (https://www.insectt.eu/).
*
* (Licensing)
* TBD
*/


#include "InputHandlingStrategy.h"

#include "util/exceptions/V2XPlatformExceptions.h"
#include "util/logger/ClassStandardOutputLogger.h"

// --- --- Public --- ---

InputHandlingStrategy::InputHandlingStrategy(std::string strategy_type, Logger::LogLevel log_level) {
    strategy_type_ = strategy_type;
    logger_ = new ClassStandardOutputLogger(log_level, strategy_type_);
}

InputHandlingStrategy::~InputHandlingStrategy() {
    delete logger_;
}

std::string InputHandlingStrategy::StrategyType() {
    return strategy_type_;
}

void InputHandlingStrategy::Configure(){
    logger_->WriteFatalEntry("Configure(): Not yet implemented ... throwing exception");
    throw NotImplementedException();
}

void InputHandlingStrategy::StartUp(){
    logger_->WriteFatalEntry("StartUp(): Not yet implemented ... throwing exception");
    throw NotImplementedException();
}

void InputHandlingStrategy::ShutDown(){
    logger_->WriteFatalEntry("ShutDown(): Not yet implemented ... throwing exception");
    throw NotImplementedException();
}

void InputHandlingStrategy::Cleanup(){
    logger_->WriteFatalEntry("Cleanup(): Not yet implemented ... throwing exception");
    throw NotImplementedException();
}

void InputHandlingStrategy::run() {
    logger_->WriteInfoEntry("run()");

    // Check if thread is requested to stop ?
    while (stopRequested() == false) {
        logger_->WriteTraceEntry("run(): loop start");

        // do magic handle stuff
        if (HandleInput() != 0){
            logger_->WriteWarnEntry("run(): HandleInput Error! -> fix that!");
            logger_->WriteFatalEntry("run(): HandleInput Error! -> going to stop");
            stop();
        }

        // yield each cycle
//        std::this_thread::yield();
        //using sleep will put the thread in a special queue, depending on implementation (https://stackoverflow.com/questions/17325888/c11-thread-waiting-behaviour-stdthis-threadyield-vs-stdthis-thread)
        //sleep_for might be necessary to avoid CPU blocking!
        std::this_thread::sleep_for(std::chrono::microseconds(100));  // 0.1ms = 10000Hz
    }

    logger_->WriteInfoEntry("run(): end");
}

void InputHandlingStrategy::SetConnectionsReference(std::list<V2XInterfaceConnection *> &connections_reference) {
    connections_reference_ = connections_reference;
}

// --- --- Protected --- ---


// --- --- Private --- ---
