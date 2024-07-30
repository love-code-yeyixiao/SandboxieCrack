# Sandboxie Plus / Classic

[![Лицензия Plus](https://img.shields.io/badge/Plus%20license-Custom%20-blue.svg)](./LICENSE.Plus) [![Лицензия Classic](https://img.shields.io/github/license/Sandboxie-Plus/Sandboxie?label=Classic%20license&color=blue)](./LICENSE.Classic) [![Релиз GitHub](https://img.shields.io/github/release/sandboxie-plus/Sandboxie.svg)](https://github.com/sandboxie-plus/Sandboxie/releases/latest) [![Предварительный релиз GitHub](https://img.shields.io/github/release/sandboxie-plus/Sandboxie/all.svg?label=pre-release)](https://github.com/sandboxie-plus/Sandboxie/releases) [![Статус сборки GitHub](https://github.com/sandboxie-plus/Sandboxie/actions/workflows/main.yml/badge.svg)](https://github.com/sandboxie-plus/Sandboxie/actions) [![Статус Codespell GitHub](https://github.com/sandboxie-plus/Sandboxie/actions/workflows/codespell.yml/badge.svg)](https://github.com/sandboxie-plus/Sandboxie/actions/workflows/codespell.yml)

[![Присоединяйтесь к нашему серверу Discord](https://img.shields.io/badge/Join-Our%20Discord%20Server%20for%20bugs,%20feedback%20and%20more!-blue?style=for-the-badge&logo=discord)](https://discord.gg/S4tFu6Enne)

[![English](https://img.shields.io/badge/English-black)](README.md)
[![وثيقة العربية](https://img.shields.io/badge/%D9%88%D8%AB%D9%8A%D9%82%D8%A9%20%D8%A7%D9%84%D8%B9%D8%B1%D8%A8%D9%8A%D8%A9-green)](README_ar.md) 
[![中文文档](https://img.shields.io/badge/%E4%B8%AD%E6%96%87%E6%96%87%E6%A1%A3-red)](README_zh.md) 
[![Document Français](https://img.shields.io/badge/Document%20Fran%C3%A7ais-white)](README_fr.md) 
[![Документ на русском языке](https://img.shields.io/badge/%D0%94%D0%BE%D0%BA%D1%83%D0%BC%D0%B5%D0%BD%D1%82%20%D0%BD%D0%B0%20%D1%80%D1%83%D1%81%D1%81%D0%BA%D0%BE%D0%BC%20%D1%8F%D0%B7%D1%8B%D0%BA%D0%B5-blue)](README_ru.md) 
[![Documento en Español](https://img.shields.io/badge/Documento%20en%20Espa%C3%B1ol-yellow)](README_es.md)

|  Системные требования  |      Примечания к релизу     |     Руководство по вкладу   |      Политика безопасности      |      Кодекс поведения      |
|         :---:         |          :---:         |          :---:                |          :---:            |          :---:            |
| Windows 7 или выше, 32-разрядная или 64-разрядная. |  [CHANGELOG.md](./CHANGELOG.md)  |  [CONTRIBUTING.md](./CONTRIBUTING.md)  |   [SECURITY.md](./SECURITY.md)  |  [CODE_OF_CONDUCT.md](./CODE_OF_CONDUCT.md)  |

Sandboxie - это программное обеспечение для изоляции, основанное на технологии "песочницы" для 32-битных и 64-битных операционных систем на основе Windows NT. Он создает изолированную операционную среду, подобную "песочнице", в которой приложения могут запускаться или устанавливаться без постоянного изменения локальных и смонтированных дисков или реестра Windows. Изолированная виртуальная среда позволяет контролируемо тестировать ненадежные программы и просматривать веб-страницы.<br>

Sandboxie позволяет создавать практически неограниченное количество "песочниц" и запускать их отдельно или одновременно для изоляции программ от хоста и друг от друга, а также позволяет запускать любое количество программ в одной "песочнице" по вашему желанию.

**Примечание: это общественная вилка, которая возникла после выпуска исходного кода Sandboxie и не является официальным продолжением предыдущей разработки (см. [историю проекта](./README.md#-project-history) и [#2926](https://github.com/sandboxie-plus/Sandboxie/issues/2926)).**

## ⏬ Скачать

[Последний релиз](https://github.com/sandboxie-plus/Sandboxie/releases/latest)

## 🚀 Особенности

Sandboxie доступен в двух версиях: Plus и Classic. Они оба используют одни и те же основные компоненты, что означает, что у них одинаковый уровень безопасности и совместимости.
Различие заключается в доступности функций в пользовательском интерфейсе.

Sandboxie Plus имеет современный интерфейс на основе Qt, который поддерживает все новые функции, добавленные после того, как проект стал открытым исходным кодом:

  * Менеджер снимков - делает копию любой "песочницы" для восстановления при необходимости
  * Режим обслуживания - позволяет удалять/устанавливать/запускать/останавливать драйвер и службу Sandboxie при необходимости
  * Портативный режим - вы можете запустить установщик и выбрать извлечение всех файлов в каталог
  * Дополнительные параметры интерфейса для блокировки доступа к компонентам Windows, таким как спулер принтера и буфер обмена
  * Дополнительные параметры настройки для ограничений запуска/работы и доступа в Интернет
  * Режим конфиденциальности, который защищает данные пользователя от незаконного доступа
  * Улучшенные с точки зрения безопасности "песочницы", ограничивающие доступ к системным вызовам и конечным точкам
  * Глобальные горячие клавиши для приостановки или завершения всех процессов в "песочнице"
  * Сетевой брандмауэр для каждой "песочницы", поддерживающий Windows Filtering Platform (WFP)
  * Список "песочниц" можно искать с помощью клавиши быстрого доступа Ctrl+F
  * Функция поиска для глобальных настроек и опций "песочницы"
  * Возможность импорта/экспорта "песочниц" в и из файлов 7z
  * Интеграция "песочниц" в меню "Пуск" Windows
  * Мастер совместимости браузера для создания шаблонов для неподдерживаемых браузеров
  * Режим винтажного вида для воспроизведения графического интерфейса Sandboxie Control
  * Мастер устранения неполадок для помощи пользователям в решении их проблем
  * Менеджер дополнений для расширения или добавления функциональности через дополнительные компоненты
  * Защита "песочниц" от хоста, включая предотвращение создания скриншотов
  * Система триггеров для выполнения действий, когда "песочница" проходит через различные этапы, такие как инициализация, запуск, завершение или восстановление файлов
  * Сделать процесс несекционированным, но его дочерние процессы секционированными
  * Использование "песочницы" как единицы управления для принудительного автоматического использования программами прокси-сервера SOCKS5
  * Контроль разрешения DNS с "песочницей" как единицей управления
  * Ограничение количества процессов в "песочнице" и общего объема памяти, которую они могут занимать, и Вы можете ограничить общее количество процессов в "песочнице" на коробку
  * Совершенно другой механизм создания токенов по сравнению с версией Sandboxie до выхода открытого кода делает "песочницы" более независимыми в системе
  * Зашифрованная "песочница" - надежное хранилище данных на основе AES.

Больше функций можно найти, используя знак = через клавишу быстрого доступа Ctrl+F в файле [CHANGELOG.md](./CHANGELOG.md).

Sandboxie Classic имеет старый интерфейс на основе MFC, который больше не развивается, поэтому он не поддерживает нативный интерфейс для функций Plus. Хотя некоторые из недостающих функций можно настроить вручную в конфигурационном файле Sandboxie.ini или даже заменить [кастомными скриптами](https://sandboxie-website-archive.github.io/www.sandboxie.com/old-forums/viewforum1a2d1a2d.html?f=22), версия Classic не рекомендуется для пользователей, которые хотят изучить новейшие параметры безопасности.

## 📚 Документация

Копия [документации Sandboxie](https://sandboxie-plus.github.io/sandboxie-docs) на GitHub в настоящее время поддерживается, хотя требуется больше волонтеров для её обновления с новыми изменениями. Мы также рекомендуем проверять следующие метки в этом репозитории:

[будущее развитие](https://github.com/sandboxie-plus/Sandboxie/issues?q=label%3A"future+development") | [запросы функций](https://github.com/sandboxie-plus/Sandboxie/issues?q=label%3A"Feature+request") | [документация](https://github.com/sandboxie-plus/Sandboxie/issues?q=label%3Adocumentation) | [проблемы сборки](https://github.com/sandboxie-plus/Sandboxie/issues?q=label%3A%22build+issue%22) | [несовместимости](https://github.com/sandboxie-plus/Sandboxie/issues?q=label%3Aincompatibility) | [известные проблемы](https://github.com/sandboxie-plus/Sandboxie/labels/Known%20issue) | [регрессии](https://github.com/sandboxie-plus/Sandboxie/issues?q=is%3Aissue+is%3Aopen+label%3Aregression) | [обходные пути](https://github.com/sandboxie-plus/Sandboxie/issues?q=label%3Aworkaround) | [требуется помощь](https://github.com/sandboxie-plus/Sandboxie/issues?q=label%3A%22help+wanted%22) | [больше...](https://github.com/sandboxie-plus/Sandboxie/labels?sort=count-desc)

Частичный архив [старого форума Sandboxie](https://sandboxie-website-archive.github.io/www.sandboxie.com/old-forums), ранее поддерживаемого Invincea, все еще доступен. Если вам нужно найти что-то конкретное, можно использовать следующий поисковый запрос: site:https://sandboxie-website-archive.github.io/www.sandboxie.com/old-forums/


## 🚀 Полезные инструменты для Sandboxie

Функциональность Sandboxie можно улучшить с помощью специализированных инструментов, таких как следующие:

  * [LogApiDll](https://github.com/sandboxie-plus/LogApiDll) - добавляет подробный вывод в журнал трассировки Sandboxie, перечисляя вызовы соответствующих функций Windows API
  * [SbieHide](https://github.com/VeroFess/SbieHide) - пытается скрыть присутствие SbieDll.dll от приложения, работающего в "песочнице"
  * [SandboxToys2](https://github.com/blap/SandboxToys2) - позволяет отслеживать изменения файлов и реестра в "песочнице"
  * [Sbiextra](https://github.com/sandboxie-plus/sbiextra) - добавляет дополнительные ограничения в режиме пользователя для процессов в "песочнице"


## 📌 История проекта

|      Хронология       |    Поддержка    |
|        :---         |       :---       |
| 2004 - 2013         | Ронен Цур       |
| 2013 - 2017         | Invincea Inc.    |
| 2017 - 2020         | Sophos Group plc |
| [Исходный код](https://github.com/sandboxie/sandboxie) |    Том Браун     |
| --- | --- |
| С 2020 года        | Дэвид Ксанатос ([Дорожная карта](https://www.wilderssecurity.com/threads/sandboxie-roadmap.445545/page-8#post-3187633))    |


## 📌 Поддержка проекта / спонсорство

[<img align="left" height="64" width="64" src="./.github/images/binja-love.png">](https://binary.ninja/)
Спасибо [Vector 35](https://vector35.com/) за предоставление лицензии [Binary Ninja](https://binary.ninja/) для помощи в реверс-инжиниринге.
<br>
Binary Ninja - это многоплатформенный интерактивный дизассемблер, декомпилятор и инструмент для анализа двоичных файлов для специалистов по реверс-инжинирингу, аналитиков вредоносных программ, исследователей уязвимостей и разработчиков программного обеспечения.
<br>
<br>
[<img align="left" height="64" width="64" src="./.github/images/Icons8_logo.png">](https://icons8.de/)Спасибо [Icons8](https://icons8.de/) за предоставление иконок для проекта.
<br>
<br>
<br>

## 🤝 Поддержите проект

Если вы считаете Sandboxie полезным, не стесняйтесь внести свой вклад, следуя [Руководству по вкладу](./CONTRIBUTING.md).

## 📑 Полезные участники

- DavidBerdik - Поддержка [Архива сайта Sandboxie](https://github.com/Sandboxie-Website-Archive/sandboxie-website-archive.github.io)
- Jackenmen - Поддержка пакетов Chocolatey для Sandboxie ([поддержка](https://github.com/Jackenmen/choco-auto/issues?q=is%3Aissue+Sandboxie))
- vedantmgoyal9 - Поддержка Winget Releaser для Sandboxie ([поддержка](https://github.com/vedantmgoyal9/winget-releaser/issues?q=is%3Aissue+Sandboxie))
- blap - Поддержка дополнения [SandboxToys2](https://github.com/blap/SandboxToys2)
- diversenok - Анализ безопасности и PoCs / Исправления безопасности
- TechLord - Команда IRA / Реверс-инжиниринг
- hg421 - Анализ безопасности и PoCs / Обзоры кода
- hx1997 - Анализ безопасности и PoC
- mpheath - Автор установщика Plus / Исправления кода / Сотрудник
- offhub - Дополнения документации / Исправления кода / Сотрудник
- isaak654 - Шаблоны / Документация / Исправления кода / Сотрудник
- typpos - Дополнения интерфейса пользователя / Документация / Исправления кода
- Yeyixiao - Дополнения функций
- Deezzir - Дополнения функций
- okrc - Исправления кода
- Sapour - Исправления кода
- lmou523 - Исправления кода
- sredna - Исправления кода для установщика Classic
- weihongx9315 - Исправление кода
- jorgectf - Workflow CodeQL
- stephtr - CI / Сертификация
- yfdyh000 - Поддержка локализации для установщика Plus
- Dyras - Дополнения шаблонов
- cricri-pingouin - Исправления интерфейса пользователя
- Valinwolf - Интерфейс пользователя / Иконки
- daveout - Интерфейс пользователя / Иконки
- NewKidOnTheBlock - Исправления changelog
- Naeemh1 - Дополнения документации
- APMichael - Дополнения шаблонов
- 1mm0rt41PC - Дополнения документации
- Luro223 - Дополнения документации
- lwcorp - Дополнения документации
- wilders-soccerfan - Дополнения документации
- LumitoLuma - Патч Qt5 и скрипт сборки
- SNESNya - Дополнения документации

## 🌏 Переводчики

- yuhao2348732, 0x391F, nkh0472, yfdyh000, gexgd0419, Zerorigin, UnnamedOrange, DevSplash, Becods, okrc, 4rt3mi5, sepcnt - Упрощенный китайский
- TragicLifeHu, Hulen, xiongsp - Традиционный китайский
- RockyTDR - Нидерландский
- clexanis, Mmoi-Fr, hippalectryon-0, Monsieur Pissou - Французский (предоставлен по электронной почте)
- bastik-1001, APMichael - Немецкий
- timinoun - Венгерский (предоставлен по электронной почте)
- isaak654, DerivativeOfLog7 - Итальянский
- takahiro-itou - Японский
- VenusGirl - Корейский
- 7zip - Польский ([предоставлен отдельно](https://forum.xanasoft.com/viewtopic.php?f=12&t=4&start=30))
- JNylson - Португальский и бразильский португальский
- lufog - Русский
- LumitoLuma, sebadamus - Испанский
- 1FF, Thatagata - Шведский (предоставлен по электронной почте или запросу на вытягивание)
- xorcan, fmbxnary, offhub - Турецкий
- SuperMaxusa, lufog - Украинский
- GunGunGun - Вьетнамский

Всех переводчиков настоятельно рекомендуется ознакомиться с [заметками и советами по локализации](https://git.io/J9G19) перед отправкой перевода.
