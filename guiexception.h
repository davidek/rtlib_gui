#ifndef GUIEXCEPTION_H
#define GUIEXCEPTION_H

#include <rttask.hpp>

using namespace RTSim;

    /**
        Base Class for the exceptions of the GUI

        @author Casini Daniel
    */
    class GUIException : public BaseExc
    {
    public:
      inline GUIException(const string message, const string cl, const string md = "MP_RTSIM_GUI") : BaseExc(message, cl, md) {}
    };

    /**
        Exception raised whenever the JSON format of a file used to load task set is not correct

        @author Casini Daniel
    */
    class NotValidTaskSetJSONFormatException : public GUIException
    {
    public:
      inline NotValidTaskSetJSONFormatException(const string message, const string cl = "TaskSetLoader", const string md = "MP_RTSIM_GUI") : GUIException(message, cl, md) {}
    };

    /**
        Exception raised whenever the JSON format of a file used to load a
        simulation traceis not correct

        @author Casini Daniel
    */
    class NotValidTraceJSONFormatException : public GUIException
    {
    public:
      inline NotValidTraceJSONFormatException(const string message, const string cl = "TraceParser", const string md = "MP_RTSIM_GUI") : GUIException(message, cl, md) {}
    };

    /**
        Exception raised whenever the JSON format of a file used to load an
        architecture (cpu-scheduler and task-cpu correspondence) is not correct

        @author Casini Daniel
    */
    class NotValidArchitectureJSONFormatException : public GUIException
    {
    public:
      inline NotValidArchitectureJSONFormatException(const string message, const string cl = "ArchitectureLoader", const string md = "MP_RTSIM_GUI") : GUIException(message, cl, md) {}
    };

    /**
        Exception raised whenever the format of the input fields is not correct

        @author Casini Daniel
    */
    class InputDataFormatException : public GUIException
    {
    public:
      inline InputDataFormatException(const string message, const string cl = "", const string md = "MP_RTSIM_GUI") : GUIException(message, cl, md) {}
    };

    /**
        Exception raised whenever the architecture (loaded from file) informations
        does not match with the task set

        @author Casini Daniel
    */
    class ArchitectureMismatchException : public GUIException
    {
    public:
      inline ArchitectureMismatchException(const string message, const string cl = "", const string md = "MP_RTSIM_GUI") : GUIException(message, cl, md) {}
    };



#endif // GUIEXCEPTION_H
