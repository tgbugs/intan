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
----
0) on windows the project must be built as 32bit due to some bug with qt and the okFrontPanel.dll :/
1) dont close the file while waiting for triggers to finish
2) number to specify how many up states before new file
---------
 1) do we need repeats for record on high? I dont think so...
 3) make ADC channels threshold settalbe
 4) update statusbar to count triggers
 5) numer of times to trigger is somehow getting set to 999 at the end
 6) creating files only have name extensions down to the second! fix this
 7) MASSIVE bug with trigger interface: all the values get reset to max if nothing is change >_< WAT the better way would probably just be to set those values and then when you hit run if your trigger repeat is greater than zero rock on and dont mess with any of the "oh we're going to start running after clicking trigger!" nonsense
 8) basically: completely rip out the fsm logic and fix it all up so that it makes sense and so that trigger doesnt have all the completely fucked edge cases
 9) I think the issue has to do with on_value_change for the spinbox or something :/
