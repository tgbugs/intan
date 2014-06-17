num_channels = 64;
%num_channels = length(amplifier_channels); % amplifier channel info from header file
fileinfo = dir('test_140613_120312.dat')
num_samples = fileinfo.bytes/(num_channels * 2); % int16 = 2 bytes
fid = fopen('test_140613_120312.dat', 'r');
v = fread(fid, [num_channels, num_samples], 'int16');
fclose(fid);
v = v * 0.195; % convert to microvolts

plot(v(32,:))