Implementaci seriálu jsem přenesl do `neco.h`, takže teď je možné přidávat logy v každém ze souborů (`serial_puts("text\n")`.

Nevím, jestli `serial_puts("text\n")` takhle můžu dát do interruptů, ale pokud ano, tak to vypadá, že jeden z interruptů, ve kterém právě probíhá příjem dat z myši, se nikdy nespouští, je to ten s `serial_puts("rec\n");`.
Takže asi zde je jádro problému. Asi myš nic neposílá, protože nesvítí.

S programem z kroužku (než jsem flashnul svůj domácí program) včera myš svítíla, ačkoli data taky nebyla příjímána (`ps2_avail()` nebylo nikdy true), dříve dnes, se stejným programem však blikala.
Možná se jedná o variability v zapojení (vyskočil drátek, a nevšiml jsem si toho)

V každém případě, ať už svítí, bliká, nebo nesvítí, data se do PC přes serial nedostanou.

Od kroužku jsem zmenšil mainMujMod.c, aby tam byly jenom ps2 věci, protože mi předchozí soubor z kroužku nešel kompilovat (když jsem napsal příkaz make, dostával jsem proud tohoto:

```
avr-objdump: Dwarf Error: found dwarf version '0', this reader only handles version 2, 3 and 4 information.
avr-objdump: Dwarf Error: found dwarf version '74', this reader only handles version 2, 3 and 4 information.
avr-objdump: Dwarf Error: found dwarf version '451', this reader only handles version 2, 3 and 4 information.
avr-objdump: Dwarf Error: found dwarf version '34055', this reader only handles version 2, 3 and 4 information.
avr-objdump: Dwarf Error: found dwarf version '2816', this reader only handles version 2, 3 and 4 information.
...
```
(bylo toho víc, celkem náhodná čísla))

tak jsem tam nechal míň věcí, serial funguje, logy v hlavním souboru se do pc dostanou všechny až do  `serial_puts("in ps2 avail\n");` 
Z logů v ps2.c vidím jenom periodicky:
```
rerec2
c
rrec2
ec
rec2
rerec2
c
rrec2
ec
rec2
recrec2

rec2
rec2
rec2
rec2
rec2
rec2
rec2
rec2
rec2
rec2
error
```

Ač teď teda jo, párkrát jsem viděl `rec` (v `recrec2` řádku, tak většinou je tam `rec2` nebo `error`.

Takový je stav znalostí v úterý 30.1 19:15

 
