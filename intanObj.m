classdef intanObj < handle
    properties %basic
        SampleRate 
        SamplesPerTrigger % call to evalBoard->setMaxTimeStep(n), evalBoard->setContinuousRunMode(false) FIXME this is gonna be hairy
        TriggerType       % there is a big difference between ACQUISITION and RUNNING
    end
    %Channel
    properties %trigger properties
        InitalTriggerTime
        ManualTriggerHwOn
        TriggerChannel
        TriggerCondition
        TriggerConditionValue
        TiggerDelay
        TriggerDelayUnits
        TriggerFcn
        TriggerRepeat
        TriggersExecuted
        %TriggerType %hrm
    end
    properties %loggin properites
        LogFileName
        Logging
        LoggingMode
        LogToDiskMode
    end
    properties %status properties
        %Logging %hrm
        Running
        SamplesAcquired
        SamplesAvailable
    end
    properties %hardware configuration properties
        ChannelSkew
        ChannelSkewMode
        ClockSource
        InputType
        %SampleRate %hrm
    end
    properties %callback properties
        DataMissedFcn
        InputOverRangeFcn
        RuntimeErrorFcn
        %SamplesAcquired %hrm
        SamplesAcquiredFcn %
        SamplesAcquiredFcnCount
        StartFcn
        StopFcn
        TimerFcn
        TimerPeriod
        %TriggerFcn %hrm
    end
    properties %general purpose properties
        BufferingConfig
        BufferingMode
        Channel = [intanChannel();];
        EventLog
        Name
        Tag
        Timeout
        Type
        UserData
    end
    properties %intan specific properties
        Bandwidth
    end
    
    methods
        function obj = intanObj()
            obj.Type = class(obj)
            %make sure the board is on/present
        end
        
        function value = get(obj,name)
            value = obj.(name);
        end
        
        function set(obj,name,value)
            obj.(name) = value; %type check??
        end
        
        function start(obj)
            'start'
            %set all the intan register values
            
            %prep all the channels for acquisition
            
            %create the queue we are going to use to read data
        end
        
        function stop(obj)
            'stop'
        end

        function activateTrigger(obj)
            'trigger'
            obj.TriggerFcn() %call the trigger function
            obj.startRecord()
        end
        
        function chans = addchannel(obj, hwch, varargin)
            %index n be increasing
            %all channel names also populate references
            varargin
            if size(varargin,2) == 2
                indexs = varargin{1}
                names = varargin{2}
            elseif size(varargin,2) == 1
                if iscell(varargin{1}) %FIXME this logic isnt right
                    names = varargin{1}
                    indexs = []
                else
                    indexs = varargin{1}
                    names = {}
                end
            else
                indexs = []
                names = {}
            end
            
            len = size(hwch,2)
            if size(indexs) & size(names)
                if size(hwch) == size(indexs) & size(hwch) == size(names)
                    for n = 1:len
                        chans(n) = intanChannel(obj, hwch(n), indexs(n), names(n))
                        obj.Channel(indexs(n)) = chans(n)
                    end
                end
            elseif size(indexs)
                if size(hwch) == size(indexs)
                    for n = 1:len
                        chans(n) = intanChannel(obj, hwch(n), indexs(n), '')
                        obj.Channel(indexs(n)) = chans(n)
                    end
                end
            elseif size(names)
                start = max(obj.Channel.Index) %broken
                if size(hwch) == size(names)
                    for n = 1:len
                        chans(n) = intanChannel(obj, hwch(n), n + start, names(n))
                        obj.Channel(n + start) = chans(n)
                    end
                end
            else
                start = max(obj.Channel.Index)
                for n = 1:len
                    chans(n) = intanChannel(obj, hwch(n), n + start, '')
                    obj.Channel(n + start) = chans(n)
                end
            end
        end

    end
    methods (Access = 'private')
        %intan logic goes here
        function startRecord(obj) %do not pass as callback, pass activateTrigger
            %RhD2000EvalBoard::readDataBlock
        end
        function stopRecord(obj)
        end
    end
end

