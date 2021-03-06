﻿using System;
using System.IO;

namespace PathManagerCustomAction
{
    enum PathVariableAction
    {
        InstallPathVariable,
        UninstallPathVariable
    }

    class ArgumentParser
    {
        const string INSTALL_PATH_ARGUMENT = "--install-path";
        const string UNINSTALL_PATH_ARGUMENT = "--uninstall-path";
        const int REQUIRED_ARGUMENT_COUNT = 2;

        public ArgumentParser(string[] arguments)
        {
            _arguments = arguments;
            if (!IsArgCountCorrect())
            {
                throw new ArgumentException("The argument count is incorrect.");
            }

            SetArgumentsAndCheckValidity();
        }

        void SetArgumentsAndCheckValidity()
        {
            SetActionFromArgs();
            if (!IsActionValid())
            {
                throw new ArgumentException("The action argument is invalid.");
            }

            SetPathFromArgs();
            if (!IsPathValid())
            {
                throw new ArgumentException("The path argument is invalid.");
            }
        }

        void SetActionFromArgs()
        {
            const int FIRST_ARGUMENT = 0;
            _action = _arguments[FIRST_ARGUMENT];
        }

        void SetPathFromArgs()
        {
            const int SECOND_ARGUMENT = 1;
            _path = _arguments[SECOND_ARGUMENT];
        }

        public PathVariableAction GetActionValue()
        {
            return ConvertToPathAction();
        }

        PathVariableAction ConvertToPathAction()
        {
            if (_action == INSTALL_PATH_ARGUMENT)
            {
                return PathVariableAction.InstallPathVariable;
            }
            else
            {
                return PathVariableAction.UninstallPathVariable;
            }
        }

        bool IsActionValid()
        {
            return _action == INSTALL_PATH_ARGUMENT || _action == UNINSTALL_PATH_ARGUMENT;
        }

        bool IsPathValid()
        {
            return Directory.Exists(_path);
        }

        bool IsArgCountCorrect()
        {
            return _arguments.Length == REQUIRED_ARGUMENT_COUNT;
        }

        public string GetProgramPath()
        {
            return _path;
        }

        string[] _arguments;
        string _path, _action;
    }
}