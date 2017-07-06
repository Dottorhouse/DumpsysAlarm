# DumpsysAlarm
A GUI around the "adb shell dumpsys alarm" command for Android.
A common problem with Android development is that is difficult to inspect scheduled alarms created via AlarmManager. It's possible to see a list of scheduled alarms with the command "adb shell dumpsys alarm", but the output is quite hard to understand.
This project is nothing more than a GUI around that command, to see in a visual, user-friendly way all of the scheduled alarms in your device.

Here's a screenshot of the running application with a list of the scheduled alarms, grouped in batches:

![Screenshot 1](https://github.com/Dottorhouse/DumpsysAlarm/blob/master/images/Screen_001.png)

There's a primitive filtering functionality implemented at the moment. You have to write the full package name and refresh via Menu or F5 shortcut. You will see only the alarm of your interest:

![Screenshot 2](https://github.com/Dottorhouse/DumpsysAlarm/blob/master/images/Screen_002.png)

Of course there's still a lot of work to be done, but I think this is enough for a first version. At least you can see if your scheduling worked as expected.
