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

#include "OutputHandlingStrategy.h"

#include "util/exceptions/V2XPlatformExceptions.h"
#include "util/logger/ClassStandardOutputLogger.h"

// --- --- Public --- ---

OutputHandlingStrategy::OutputHandlingStrategy(std::string strategy_type, Logger::LogLevel log_level) {
    strategy_type_ = strategy_type;
    logger_ = new ClassStandardOutputLogger(log_level, strategy_type_);
}

OutputHandlingStrategy::~OutputHandlingStrategy() {
    delete logger_;
}

std::string OutputHandlingStrategy::StrategyType() {
    return strategy_type_;
}

void OutputHandlingStrategy::Configure(){
    logger_->WriteFatalEntry("Configure(): Not yet implemented ... throwing exception");
    throw NotImplementedException();
}

void OutputHandlingStrategy::StartUp(){
    logger_->WriteFatalEntry("StartUp(): Not yet implemented ... throwing exception");
    throw NotImplementedException();
}

void OutputHandlingStrategy::ShutDown(){
    logger_->WriteFatalEntry("ShutDown(): Not yet implemented ... throwing exception");
    throw NotImplementedException();
}

void OutputHandlingStrategy::Cleanup(){
    logger_->WriteFatalEntry("Cleanup(): Not yet implemented ... throwing exception");
    throw NotImplementedException();
}

void OutputHandlingStrategy::run() {
    logger_->WriteInfoEntry("run()");

    // Check if thread is requested to stop ?
    while (stopRequested() == false) {
        logger_->WriteTraceEntry("run(): loop start");

        // do magic handle stuff
        if (HandleOutput() != 0){
            logger_->WriteWarnEntry("run(): HandleOutput Error! -> fix that!");
            logger_->WriteFatalEntry("run(): HandleOutput Error! -> going to stop");
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

void OutputHandlingStrategy::SetConnectionsReference(std::list<V2XInterfaceConnection *> &connections_reference) {
    connections_reference_ = connections_reference;
}

// --- --- Protected --- ---


// --- --- Private --- ---
