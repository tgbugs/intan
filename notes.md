looks like the proper way to do this is to just write a mex file
there really isnt any other good way to do this...
fortunately this can keep things clean

well... now that I have vs2013 maybe I should just build a bloody dll...
-----------

change thresholding on analog inputs, can it be per channel dont know?

need to trigger a stop based on time or rather number of samples
only acquire during ttl high (perfer ttl high)
	add the callback for stop from an input...

change window size >_<

change trace window size

how save the file

see all channels at the same time

_____________
in addition to daq toolbox functions we need

amplifier settings:
sampling rate, bandwidth

may need rescan or initial scan

maybe impedence but can use existing if really needed


-----
a question: do you really need all of these features?
why would you not just start recording and let the thing run and have
a channel that recorded all of the experimental events
or better yet just had a time stamp or some synchronization mechanism?


------
Everything that I need is in the Rhythm API, it actually looks pretty nice...
I think it should do everything we need it to do in matlab

----------
To get past the final bug we need to add libEGLd.dll or libEGL.dll to the folder

---------
1) dont close the file while waiting for triggers to finish
2) number to specify how many up states before new file
3) make ADC channels threshold settalbe
