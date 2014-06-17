classdef intanChannel
    %INTANCHANNEL Summary of this class goes here
    %   Detailed explanation goes here
    properties %channel properties
        ChannelName
        HwChannel
        HwLine
        Index = 0; %sneeky default
        InputRange
        NativeOffset
        NativeScaling
        Parent
        SensorRange
        Type
        Units
        UnitsRange
    end
    methods
        function chan = intanChannel(parent, hwch, index, name)
            %constructor
            if nargin > 0
                chan.ChannelName = name;
                chan.HwChannel = hwch;
                chan.Index = index;
                chan.Parent = parent;
                
                chan.InputRange = [-10.0;10.0];
                chan.NativeOffset = 0;
                chan.NativeScaling = 1.0;
                chan.SensorRange = [-10.0;10.0];
                chan.UnitsRange = [-10.0;10.0];
            end
            chan.Type = class(chan);
        end

    end
end

