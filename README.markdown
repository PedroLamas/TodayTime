# TodayTime

## Small configurable Today Plugin for date & time for Windows Mobile 5.0

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
* d -> Dia do mês (1, 2, 3, ...)
* dd -> Dia do mês (01, 02, 03, ...)
* ddd -> Abreviatura do dia da semana (Dom, Seg, Ter, ...)
* dddd -> Dia da semana (Domingo, Segunda, Terça, ...)
* M -> Número do Mês de 1 a 12 (1, 2, 3)
* MM -> Número do Mês de 1 a 12 (01, 02, 03, ...)
* MMM -> Abreviatura do Mês (Jan, Fev, Mar, ...)
* MMMM -> Mês (Janeiro, Fevereiro, Março, ...)
* y -> Último 2 dígitos do ano (99, 0, 1, ...)
* yy -> Últimos 2 dígitos do ano (99, 00, 01, ...)
* yyyy -> Ano (1999, 2000, 2001, ...)
* gg -> Era (creio que é ignorado no nosso calendário)

Use the following for the Time:
* h -> Hora (8, 9, 10, 11, 12, 1, 2, ...)
* hh-> Hora (08, 09, 10, 11, 12, 01, 02, ...)
* H -> Hora (8, 9, 10, 11, 12, 13, 14, ...)
* HH -> Hora (08, 09, 10, 11, 12, 13, 14, ...)
* m -> Minuto (1, 2, 3, ...)
* mm -> Minuto (01, 02, 03, ...)
* s -> Segundos (1, 2, 3, ...)
* ss -> Segundos (01, 02, 03, ...)
* t -> A ou P
* tt -> AM ou PM
* @ -> Swatch Internet Time (@100)

You can also use the text you want, just delit it with the ' (quote). For example for a date like "Today: Sunday, March 5, 2006" you could use the format "'Today:' dddd, MMMM d, yyyy".

# License

See the [LICENSE.txt][2] file for details.


[1]: https://github.com/PedroLamas/TodayTime/raw/master/Screenshot.jpg "TodayTime"
[2]: https://github.com/PedroLamas/TodayTime/raw/master/LICENSE.txt "TodayTime License"