## TodayTime

__Small configurable Today Plugin for date & time for Windows Mobile 5.0__

![TodayTime][1]

This is a __really old project__ that I made back in 2006 for Windows Mobile 5.0, that I now want to make open-source!

Back then, it was really a huge success, having more than 80.000 downloads from multiple sites!

Here's the original text...

---

# About

For those unaware, on the latest ROM's, i-mate removed the clock from the Today Screen's title bar and put it together with the date plugin, doubling its size ... Now that's a real waste of space on the Today!

So I decided to create a small plugin that shows the date, internet time (Swatch Internet Time) and the current time! Tapping the plugin panel shows the Date/Time, as it currently does in the native Date plugin.

You can configure the plugin by going to _Start -> Settings -> Personal_ and then _Today -> Items_, pick TodayTime, tap the Options button e use the table below.

Use the following for the Date:

* __d__ -> Day of month as digits with no leading zero for single-digit days (1, 2, 3, ...)
* __dd__ -> Day of month as digits with leading zero for single-digit days (01, 02, 03, ...)
* __ddd__ -> Day of week as a three-letter abbreviation (Sun, Mon, Tue, ...)
* __dddd__ -> Day of week as its full name (Sunday, Monday, Tuesday, ...)
* __M__ -> Month as digits with no leading zero for single-digit months (1, 2, 3)
* __MM__ -> Month as digits with leading zero for single-digit months (01, 02, 03, ...)
* __MMM__ -> Month as a three-letter abbreviation (Jan, Feb, Mar, ...)
* __MMMM__ -> Month as its full name (January, February, March, ...)
* __y__ -> Year as last two digits, but with no leading zero for years less than 10 (99, 0, 1, ...)
* __yy__ -> Year as last two digits, but with leading zero for years less than 10 (99, 00, 01, ...)
* __yyyy__ -> Year represented by full four or five digits, depending on the calendar used (1999, 2000, 2001, ...)
* __gg__ -> Period/era string

Use the following for the Time:

* __h__ -> Hours with no leading zero for single-digit hours; 12-hour clock (8, 9, 10, 11, 12, 1, 2, ...)
* __hh__ -> Hours with leading zero for single-digit hours; 12-hour clock (08, 09, 10, 11, 12, 01, 02, ...)
* __H__ -> Hours with no leading zero for single-digit hours; 24-hour clock (8, 9, 10, 11, 12, 13, 14, ...)
* __HH__ -> Hours with leading zero for single-digit hours; 24-hour clock (08, 09, 10, 11, 12, 13, 14, ...)
* __m__ -> Minutes with no leading zero for single-digit minutes (1, 2, 3, ...)
* __mm__ -> Minutes with leading zero for single-digit minutes (01, 02, 03, ...)
* __s__ -> Seconds with no leading zero for single-digit seconds (1, 2, 3, ...)
* __ss__ -> Seconds with leading zero for single-digit seconds (01, 02, 03, ...)
* __t__ -> One character time-marker string, such as A or P
* __tt__ -> Multicharacter time-marker string, such as AM or PM
* __@__ -> Swatch Internet Time / swatch beats (@100)

You can also use the text you want, just delit it with the ' (quote). For example for a date like "Today: Sunday, March 5, 2006" you could use the format "'Today:' dddd, MMMM d, yyyy".

# License

See the [LICENSE.txt][2] file for details.

[1]: https://github.com/PedroLamas/TodayTime/raw/master/Screenshot.jpg "TodayTime"
[2]: https://github.com/PedroLamas/TodayTime/raw/master/LICENSE.txt "TodayTime License"