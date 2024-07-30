# Sandboxie Plus / Classic

[![Plus license](https://img.shields.io/badge/Plus%20license-Custom%20-blue.svg)](./LICENSE.Plus) [![Classic license](https://img.shields.io/github/license/Sandboxie-Plus/Sandboxie?label=Classic%20license&color=blue)](./LICENSE.Classic) [![GitHub Release](https://img.shields.io/github/release/sandboxie-plus/Sandboxie.svg)](https://github.com/sandboxie-plus/Sandboxie/releases/latest) [![GitHub Pre-Release](https://img.shields.io/github/release/sandboxie-plus/Sandboxie/all.svg?label=pre-release)](https://github.com/sandboxie-plus/Sandboxie/releases) [![GitHub Build Status](https://github.com/sandboxie-plus/Sandboxie/actions/workflows/main.yml/badge.svg)](https://github.com/sandboxie-plus/Sandboxie/actions) [![GitHub Codespell Status](https://github.com/sandboxie-plus/Sandboxie/actions/workflows/codespell.yml/badge.svg)](https://github.com/sandboxie-plus/Sandboxie/actions/workflows/codespell.yml)

[![انضم إلى خادم الديسكورد](https://img.shields.io/badge/Join-Our%20Discord%20Server%20for%20bugs,%20feedback%20and%20more!-blue?style=for-the-badge&logo=discord)](https://discord.gg/S4tFu6Enne)

[![English](https://img.shields.io/badge/English-black)](README.md)
[![وثيقة العربية](https://img.shields.io/badge/%D9%88%D8%AB%D9%8A%D9%82%D8%A9%20%D8%A7%D9%84%D8%B9%D8%B1%D8%A8%D9%8A%D8%A9-green)](README_ar.md) 
[![中文文档](https://img.shields.io/badge/%E4%B8%AD%E6%96%87%E6%96%87%E6%A1%A3-red)](README_zh.md) 
[![Document Français](https://img.shields.io/badge/Document%20Fran%C3%A7ais-white)](README_fr.md) 
[![Документ на русском языке](https://img.shields.io/badge/%D0%94%D0%BE%D0%BA%D1%83%D0%BC%D0%B5%D0%BD%D1%82%20%D0%BD%D0%B0%20%D1%80%D1%83%D1%81%D1%81%D0%BA%D0%BE%D0%BC%20%D1%8F%D0%B7%D1%8B%D0%BA%D0%B5-blue)](README_ru.md) 
[![Documento en Español](https://img.shields.io/badge/Documento%20en%20Espa%C3%B1ol-yellow)](README_es.md)
                            
|  متطلبات النظام  |      ملاحظات الإصدار     |     إرشادات المساهمة   |      سياسة الأمان      |      ميثاق السلوك      |
|         :---:         |          :---:         |          :---:                |          :---:            |          :---:            |
| Windows 7 أو أعلى ، 32 بت أو 64 بت. |  [CHANGELOG.md](./CHANGELOG.md)  |  [CONTRIBUTING.md](./CONTRIBUTING.md)  |   [SECURITY.md](./SECURITY.md)  |  [CODE_OF_CONDUCT.md](./CODE_OF_CONDUCT.md)  |

Sandboxie هو برنامج عزل يعتمد على الحماية لأنظمة التشغيل Windows NT 32 بت و 64 بت. يقوم بإنشاء بيئة تشغيل معزولة شبيهة بالصندوق الرمل حيث يمكن تشغيل التطبيقات أو تثبيتها دون تعديل دائم للأقراص المحلية والمحركات الموصولة أو سجل Windows. توفر البيئة الافتراضية المعزولة اختبارًا متحكمًا للبرامج غير الموثوق بها وتصفح الويب.<br>

يتيح لك Sandboxie إنشاء صناديق رملية غير محدودة وتشغيلها بمفردها أو في نفس الوقت لعزل البرامج عن المضيف وعن بعضها البعض ، بينما يتيح لك أيضًا تشغيل العديد من البرامج في صندوق واحد كما تشاء.

**ملاحظة: هذه شوكة مجتمعية تمت بعد إصدار شفرة مصدر Sandboxie وليست استمرارًا رسميًا للتطوير السابق (راجع [تاريخ المشروع](./README.md#-project-history) و [#2926](https://github.com/sandboxie-plus/Sandboxie/issues/2926)).**

## ⏬ تحميل

[أحدث إصدار](https://github.com/sandboxie-plus/Sandboxie/releases/latest)

## 🚀 الميزات

Sandboxie متاح في إصدارين ، Plus و Classic. يشتركان في نفس المكونات الأساسية، مما يعني أن لديهما نفس مستوى الأمان والتوافق.
الفرق هو توافر الميزات في واجهة المستخدم.

يحتوي Sandboxie Plus على واجهة مستخدم حديثة تعتمد على Qt، والتي تدعم جميع الميزات الجديدة التي تمت إضافتها منذ أن أصبح المشروع مفتوح المصدر:

  * مدير اللقطات - يأخذ نسخة من أي صندوق ليتم استعادتها عند الحاجة
  * وضع الصيانة - يتيح إلغاء تثبيت / تثبيت / بدء / إيقاف برنامج تشغيل وخدمة Sandboxie عند الحاجة
  * الوضع المحمول - يمكنك تشغيل المثبت واختيار استخراج جميع الملفات إلى دليل
  * خيارات واجهة المستخدم الإضافية لحظر الوصول إلى مكونات Windows مثل طابعة التخزين المؤقت والحافظة
  * المزيد من خيارات التخصيص للبدء / التشغيل وقيود الوصول إلى الإنترنت
  * صناديق الوضع الخصوصية التي تحمي بيانات المستخدم من الوصول غير المشروع
  * صناديق الأمان المعززة التي تقيد توافر المكالمات النظامية ونقاط النهاية
  * اختصارات لوحة المفاتيح العالمية لتعليق أو إنهاء جميع العمليات الموجودة في الصندوق
  * جدار حماية شبكي لكل صندوق يدعم Windows Filtering Platform (WFP)
  * يمكن البحث عن قائمة الصناديق باستخدام مفتاح الاختصار Ctrl+F
  * وظيفة بحث لإعدادات النظام وخيارات الصندوق
  * القدرة على استيراد / تصدير الصناديق إلى ومن ملفات 7z
  * دمج الصناديق في قائمة بدء Windows
  * معالج التوافق مع المتصفح لإنشاء قوالب للمتصفحات غير المدعومة
  * وضع العرض القديم لإعادة إنتاج الشكل الرسومي لوحدة التحكم في Sandboxie
  * معالج استكشاف الأخطاء وإصلاحها لمساعدة المستخدمين في مشاكلهم
  * مدير الإضافات لتوسيع أو إضافة وظائف عبر مكونات إضافية
  * حماية الصناديق من المضيف، بما في ذلك منع أخذ لقطات الشاشة
  * نظام الزناد لأداء الإجراءات، عندما يمر الصندوق بمراحل مختلفة، مثل التهيئة، بدء الصندوق، إنهاء أو استعادة الملفات
  * جعل عملية غير موجودة في الصندوق، ولكن العمليات الفرعية في الصندوق
  * استخدام الصندوق كوحدة تحكم لإجبار البرامج على استخدام وكيل SOCKS5 تلقائيًا
  * التحكم في دقة DNS مع الصندوق كوحدة تحكم
  * تحديد عدد العمليات في الصندوق وإجمالي المساحة الذاكرية التي يمكن أن تشغلها، ويمكنك تحديد العدد الإجمالي للعمليات في كل صندوق
  * آلية إنشاء رموز مختلفة تمامًا عن إصدار Sandboxie قبل أن يصبح مفتوح المصدر تجعل الصناديق أكثر استقلالية في النظام
  * صندوق مشفر - حل تخزين بيانات موثوق يعتمد على AES.

يمكن اكتشاف المزيد من الميزات بالبحث عن العلامة = من خلال مفتاح الاختصار Ctrl+F في ملف [CHANGELOG.md](./CHANGELOG.md).

يحتوي Sandboxie Classic على واجهة مستخدم قديمة لم تعد مدعومة تعتمد على MFC، لذا فهي تفتقر إلى دعم الواجهة الأصلية لميزات Plus. على الرغم من أنه يمكن تكوين بعض الميزات المفقودة يدويًا في ملف تكوين Sandboxie.ini أو حتى استبدالها بـ [برامج نصية مخصصة](https://sandboxie-website-archive.github.io/www.sandboxie.com/old-forums/viewforum1a2d1a2d.html?f=22)، لا ينصح باستخدام الإصدار Classic للمستخدمين الذين يرغبون في استكشاف أحدث خيارات الأمان.

## 📚 التوثيق

يتم حاليًا الحفاظ على نسخة GitHub من [توثيق Sandboxie](https://sandboxie-plus.github.io/sandboxie-docs)، على الرغم من الحاجة إلى المزيد من المتطوعين لتحديثه بالتغييرات الجديدة. نوصي أيضًا بالتحقق من الملصقات التالية في هذا المستودع:

[التطوير المستقبلي](https://github.com/sandboxie-plus/Sandboxie/issues?q=label%3A"future+development") | [طلبات الميزات](https://github.com/sandboxie-plus/Sandboxie/issues?q=label%3A"Feature+request") | [التوثيق](https://github.com/sandboxie-plus/Sandboxie/issues?q=label%3Adocumentation) | [مشاكل البناء](https://github.com/sandboxie-plus/Sandboxie/issues?q=label%3A%22build+issue%22) | [التوافقات](https://github.com/sandboxie-plus/Sandboxie/issues?q=label%3Aincompatibility) | [المشاكل المعروفة](https://github.com/sandboxie-plus/Sandboxie/labels/Known%20issue) | [الانتكاسات](https://github.com/sandboxie-plus/Sandboxie/issues?q=is%3Aissue+is%3Aopen+label%3Aregression) | [الحلول](https://github.com/sandboxie-plus/Sandboxie/issues?q=label%3Aworkaround) | [المساعدة المطلوبة](https://github.com/sandboxie-plus/Sandboxie/issues?q=label%3A%22help+wanted%22) | [المزيد...](https://github.com/sandboxie-plus/Sandboxie/labels?sort=count-desc)

أرشيف جزئي [المنتدى القديم لـ Sandboxie](https://sandboxie-website-archive.github.io/www.sandboxie.com/old-forums) الذي كان يُديره سابقًا Invincea لا يزال متاحًا. إذا كنت بحاجة إلى العثور على شيء محدد، فمن الممكن استخدام استعلام البحث التالي: site:https://sandboxie-website-archive.github.io/www.sandboxie.com/old-forums/


## 🚀 أدوات مفيدة لـ Sandboxie

يمكن تعزيز وظيفة Sandboxie باستخدام أدوات متخصصة مثل ما يلي:

  * [LogApiDll](https://github.com/sandboxie-plus/LogApiDll) - يضيف إخراجًا مفصلاً إلى سجل تتبع Sandboxie، يسرد استدعاءات وظائف Windows API ذات الصلة
  * [SbieHide](https://github.com/VeroFess/SbieHide) - يحاول إخفاء وجود SbieDll.dll من التطبيق الذي يتم تشغيله في الصندوق
  * [SandboxToys2](https://github.com/blap/SandboxToys2) - يتيح مراقبة تغييرات الملفات والسجل في الصندوق
  * [Sbiextra](https://github.com/sandboxie-plus/sbiextra) - يضيف قيودًا إضافية في وضع المستخدم على العمليات التي تعمل في الصندوق


## 📌 تاريخ المشروع

|      الجدول الزمني       |    الصيانة    |
|        :---         |       :---       |
| 2004 - 2013         | رونين تزور       |
| 2013 - 2017         | شركة Invincea Inc.    |
| 2017 - 2020         | مجموعة Sophos Group plc |
| [الشفرة مفتوحة المصدر](https://github.com/sandboxie/sandboxie) |    توم براون     |
| --- | --- |
| 2020 وما بعده        | ديفيد زاناتوس ([خارطة الطريق](https://www.wilderssecurity.com/threads/sandboxie-roadmap.445545/page-8#post-3187633))    |


## 📌 دعم المشروع / الرعاية

[<img align="left" height="64" width="64" src="./.github/images/binja-love.png">](https://binary.ninja/)
شكرًا لـ [Vector 35](https://vector35.com/) لتوفير رخصة [Binary Ninja](https://binary.ninja/) للمساعدة في الهندسة العكسية.
<br>
Binary Ninja هي أداة فك متعددة المنصات، ديكومبيلر وأداة تحليل ثنائية للمهندسين العكسيين، محللي البرمجيات الخبيثة، الباحثين في الثغرات الأمنية، والمطورين.
<br>
<br>
[<img align="left" height="64" width="64" src="./.github/images/Icons8_logo.png">](https://icons8.de/) شكرًا لـ [Icons8](https://icons8.de/) لتوفير الأيقونات للمشروع.
<br>
<br>
<br>

## 🤝 دعم المشروع

إذا وجدت Sandboxie مفيدًا، فلا تتردد في المساهمة من خلال [إرشادات المساهمة](./CONTRIBUTING.md).

## 📑 المساهمون المفيدون

- DavidBerdik - صيانة [أرشيف موقع Sandboxie](https://github.com/Sandboxie-Website-Archive/sandboxie-website-archive.github.io)
- Jackenmen - صيانة حزم Chocolatey لـ Sandboxie ([الدعم](https://github.com/Jackenmen/choco-auto/issues?q=is%3Aissue+Sandboxie))
- vedantmgoyal9 - صيانة Winget Releaser لـ Sandboxie ([الدعم](https://github.com/vedantmgoyal9/winget-releaser/issues?q=is%3Aissue+Sandboxie))
- blap - صيانة إضافة [SandboxToys2](https://github.com/blap/SandboxToys2)
- diversenok - تحليل الأمان و PoCs / إصلاحات الأمان
- TechLord - فريق IRA / الهندسة العكسية
- hg421 - تحليل الأمان و PoCs / مراجعات الشفرات
- hx1997 - تحليل الأمان و PoC
- mpheath - مؤلف مثبت Plus / إصلاحات الشفرات / متعاون
- offhub - إضافات التوثيق / إصلاحات الشفرات / متعاون
- isaak654 - القوالب / التوثيق / إصلاحات الشفرات / متعاون
- typpos - إضافات واجهة المستخدم / التوثيق / إصلاحات الشفرات
- Yeyixiao - إضافات الميزات
- Deezzir - إضافات الميزات
- okrc - إصلاحات الشفرات
- Sapour - إصلاحات الشفرات
- lmou523 - إصلاحات الشفرات
- sredna - إصلاحات الشفرات لمثبت Classic
- weihongx9315 - إصلاح الشفرات
- jorgectf - سير العمل CodeQL
- stephtr - CI / الشهادات
- yfdyh000 - دعم الترجمة لمثبت Plus
- Dyras - إضافات القوالب
- cricri-pingouin - إصلاحات واجهة المستخدم
- Valinwolf - واجهة المستخدم / الأيقونات
- daveout - واجهة المستخدم / الأيقونات
- NewKidOnTheBlock - إصلاحات التغيير
- Naeemh1 - إضافات التوثيق
- APMichael - إضافات القوالب
- 1mm0rt41PC - إضافات التوثيق
- Luro223 - إضافات التوثيق
- lwcorp - إضافات التوثيق
- wilders-soccerfan - إضافات التوثيق
- LumitoLuma - تصحيح Qt5 ونص البناء
- SNESNya - إضافات التوثيق

## 🌏 المترجمون

- yuhao2348732, 0x391F, nkh0472, yfdyh000, gexgd0419, Zerorigin, UnnamedOrange, DevSplash, Becods, okrc, 4rt3mi5, sepcnt - الصينية المبسطة
- TragicLifeHu, Hulen, xiongsp - الصينية التقليدية
- RockyTDR - الهولندية
- clexanis, Mmoi-Fr, hippalectryon-0, Monsieur Pissou - الفرنسية (مقدمة عبر البريد الإلكتروني)
- bastik-1001, APMichael - الألمانية
- timinoun - المجرية (مقدمة عبر البريد الإلكتروني)
- isaak654, DerivativeOfLog7 - الإيطالية
- takahiro-itou - اليابانية
- VenusGirl - الكورية
- 7zip - البولندية ([مقدمة بشكل منفصل](https://forum.xanasoft.com/viewtopic.php?f=12&t=4&start=30))
- JNylson - البرتغالية والبرتغالية البرازيلية
- lufog - الروسية
- LumitoLuma, sebadamus - الإسبانية
- 1FF, Thatagata - السويدية (مقدمة عبر البريد الإلكتروني أو طلب سحب)
- xorcan, fmbxnary, offhub - التركية
- SuperMaxusa, lufog - الأوكرانية
- GunGunGun - الفيتنامية

يتم تشجيع جميع المترجمين على الاطلاع على [ملاحظات وتلميحات التوطين](https://git.io/J9G19) قبل إرسال الترجمة.
