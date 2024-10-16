- Добавить заметки от Егора Б., Егора М., Федора, Вовы Ш. из разных чатов по С++.
- Поискать и смотреть все выступления Герба Саттера, Andreas Fertig, Sean Parrent, Антона Полухина.
- В игровой движок внедрить возмоность писать тесты непосредственно в файлах кода проекта, и выкидывать их из компиляции специальным макросом.
- Профилирование
  - Zelis, Herald of Krill Issues: I'm using uica https://uica.uops.info/
  - [9:51 PM]Zelis, Herald of Krill Issues: llvm-mca is also good for this
- Поискать про инструментарий TLA для формальной верификации алгоритмов
- https://github.com/oneapi-src/oneTBB - Intel Threading Building Blocks - библиотека для параллельного программирования

### Различные профилировщики и отладчики для работы с многопоточными программами

#### Профилировщики:

1. **Tracy**:
   - https://github.com/wolfpld/tracy
   - В реальном времени собирает данные о производительности.
   - Позволяет анализировать задержки, узкие места и проблемы многопоточности.
   - Поддерживает глубокую интеграцию с приложениями и имеет удобный интерфейс.

2. **VTune Profiler** (Intel):
   - Мощный инструмент от Intel для профилирования приложений.
   - Поддерживает детализированный анализ многопоточных программ, включая выявление блокировок и контеншнов.

3. **Perf**:
   - Инструмент командной строки для профилирования на Linux.
   - Может собирать информацию о производительности, включая данные по процессору, памяти, и многопоточности.

4. **gperftools** (Google Performance Tools):
   - Набор инструментов, включающий профилировщик CPU, профилировщик памяти и профилировщик для обнаружения утечек памяти.
   - Может использоваться для анализа многопоточных приложений.

5. **Instruments** (Xcode):
   - Инструмент для профилирования и анализа производительности приложений на macOS и iOS.
   - Включает в себя инструменты для анализа многопоточности и проблем синхронизации.

6. **Visual Studio Profiler**:
   - Встроенный в Visual Studio профилировщик, поддерживающий анализ производительности и многопоточности.
   - Имеет удобный графический интерфейс для анализа данных профилирования.

#### Отладчики:

1. **GDB** (GNU Debugger):
   - Широко используемый отладчик для Unix-подобных систем.
   - Поддерживает отладку многопоточных программ, включая контроль над потоками и анализ гонок данных.

2. **LLDB** (LLVM Debugger):
   - Отладчик от LLVM Project, является основным отладчиком в Xcode.
   - Поддерживает отладку многопоточных приложений, работает на macOS и Linux.

3. **WinDbg**:
   - Отладчик для Windows от Microsoft, поддерживает анализ многопоточных программ.
   - Поддерживает мощные сценарии для анализа dump-файлов и сложных многопоточных ситуаций.

4. **Valgrind** (с инструментом Helgrind):
   - Мощный инструмент для динамического анализа программ, который может обнаруживать гонки данных и проблемы с блокировками.
   - Helgrind — это инструмент для анализа многопоточности, работающий на базе Valgrind.

5. **Sanitizers**:
   - **ThreadSanitizer (TSan)**: инструмент для выявления гонок данных в многопоточных приложениях.
   - **AddressSanitizer (ASan)**: помогает обнаружить ошибки работы с памятью, которые могут быть вызваны проблемами синхронизации.

6. **Visual Studio Debugger**:
   - Поддерживает отладку многопоточных программ с возможностью управления потоками, анализа стека вызовов и синхронизации.

Эти инструменты помогают разработчикам обнаруживать и решать проблемы с многопоточными программами, обеспечивая стабильность и производительность их приложений.
