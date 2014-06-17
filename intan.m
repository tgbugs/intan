%the order of things
%.m start
%.c set all the values
%.c check out the trigger type
%.c depending on the trigger type we may need to listent for software
%.c for some reason I think that this needs to be async ??? otherwise how do we connect back to a running task?!
%.c got trigger
%.c start recording
%.m nothing...
%
%shit, this isnt going to work right, we need *something* that continues to run and can be queried asyncrhonously
%
%alright: solutions: http://mathworks.com/matlabcentral/newsreader/view_thread/278243
%basically we need need to spawn off a c++ class/objct and not clean it up
%after creation we return and store the value of that pointer so that we
%can call back in to it every time we call another mex function
%only when we call cleanup will we deallocate the memory and remove the pointer
%this way we can keep the evalboard and registers persistent

%may also try hsetget?
classdef intan % < handle %handle implements a cleanup method very useful for this
    %INTANMEX set of functions to call into the monolithic mex file
    %   Detailed explanation goes here
    
    properties (Access = 'private') %function names
        Function = 'name';
    end
    properties %these corrispond directly to function names in intanMex
        cpp_handle %uint64 pointer to the cpp object (class) that does all the stuff we need, needs to be public for mxGetProperty to work
        SampleRateArray

        SampleRate
        SamplesPerTrigger
        TriggerRepeat
        LogFileName
        LogToDiskMode %
        LoggingMode %
    end

    methods %set methods
        function out = set(obj,name,value)
            out = intanMex(obj,name,value);
            if out >= 0 %if our set was successful
                obj.(name) = value
            end
        end
        function out = setValue(obj,value) %test
            out = intanMex(obj,'setValue',value);
        end  
    end

    methods %get methods
        function out = isRunning(obj);
            out = intanMex(obj,'isRunning');
        end
        function out = start(obj)
            out = intanMex(obj,'start');
        end
        function out = stop(obj)
            out = intanMex(obj,'stop');
        end
        function out = softwareTrigger(obj)
            out = intanMex(obj,'softwareTrigger');
        end
    end

    methods %callback handler?? or call directly to TriggerFcn?
        function wat()
        end
        function TriggerFcn()
            'You rang?'
        end
    end

    methods %class methods
        function obj = intan()
            temp = intanMex(obj,'create'); %return a new cpp_handle
            obj.cpp_handle = temp;
            initReturn = intanMex(obj,'init');

            obj.SampleRateArray = {   'SampleRate1000Hz', %strings used by the enum
            'SampleRate1250Hz',
            'SampleRate1500Hz',
            'SampleRate2000Hz',
            'SampleRate2500Hz',
            'SampleRate3000Hz',
            'SampleRate3333Hz',
            'SampleRate4000Hz',
            'SampleRate5000Hz',
            'SampleRate6250Hz',
            'SampleRate8000Hz',
            'SampleRate10000Hz',
            'SampleRate12500Hz',
            'SampleRate15000Hz',
            'SampleRate20000Hz',
            'SampleRate25000Hz',
            'SampleRate30000Hz'}
        end
        function addlistener()
            'adds a listener for an event w/ a callback...'
        end
        function delete(obj)
            %clear_mex(obj.cpp_handle); %not sure how this works?
            intanMex(obj,'delete')
            %'delete'
            %clean it up
        end
    end
end
