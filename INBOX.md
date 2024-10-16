# INBOX - Books, Links, Projects, Tools and any other stuff

- [Notes from leozz37](#notes-from-leozz37)
  - [C++ Books](#c-books)
  - [Programming in general](#programming-in-general)
  - [Links](#links)
  - [Projects](#projects)
  - [Tools - Online Compilers](#tools---online-compilers)
  - [Tools - CI](#tools---ci)
  - [Tools - Code Quality](#tools---code-quality)
  - [Tools - Code Coverage](#tools---code-coverage)
  - [Tools - Code Documentation](#tools---code-documentation)
  - [Tools - Sanitizers](#tools---sanitizers)
  - [Tools - Other](#tools---other)
- [Либы для работы с сетью из С++](#либы-для-работы-с-сетью-из-с)
  - [Только синхронные либы](#только-синхронные-либы)
  - [Асинхронные с поддержкой HTTP/REST API:](#асинхронные-с-поддержкой-httprest-api)
  - [Асинхронные Вебсокеты:](#асинхронные-вебсокеты)
  - [Легковесные Асинхронные HTTP-серверы:](#легковесные-асинхронные-http-серверы)
  - [Асинхронные с поддержкой событийного цикла:](#асинхронные-с-поддержкой-событийного-цикла)
  - [Асинхронные - с поддержкой HTTP/2:](#асинхронные---с-поддержкой-http2)
- [Modern Dependency Walker](#modern-dependency-walker)

## Notes from leozz37

- https://github.com/leozz37/books?tab=readme-ov-file

### C++ Books

- [A Tour of C++](https://www.amazon.com.br/Tour-C-2nd-Bjarne-Stroustrup/dp/0134997832/ref=sr_1_1?__mk_pt_BR=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=1IR5XEA4IMCVQ&dchild=1&keywords=a+tour+of+c%2B%2B&qid=1597129065&sprefix=a+tour+of%2Caps%2C286&sr=8-1), Bjarne Stroustrup
- [C++ Programming Language](https://www.amazon.com.br/Programming-Language-Programm-Lang_p4-English-ebook/dp/B00DUW4BMS/ref=sr_1_6?__mk_pt_BR=%C3%85M%C3%85%C5%BD%C3%95%C3%91&dchild=1&keywords=c%2B%2B&qid=1597129178&s=digital-text&sr=1-6), Bjarne Stroustrup
- [C++ Primer](https://www.amazon.com.br/dp/B0091I7FEQ/?coliid=I2ONYYNLR64P4I&colid=1EQTD27MP9O7E&psc=0&ref_=lv_ov_lig_dp_it), Stanley B. Lippman
- [Effective Modern C++: 42 Specific Ways to Improve Your Use of C++11 and C++14](https://www.amazon.com.br/Effective-Modern-Specific-Improve-English-ebook/dp/B00PGCMGDQ/ref=sr_1_1?__mk_pt_BR=%C3%85M%C3%85%C5%BD%C3%95%C3%91&dchild=1&keywords=scott+meyers&qid=1597129283&s=digital-text&sr=1-1), Scott Meyers
- [Effective STL: 50 Specific Ways to Improve Your Use of the Standard Template Library](https://www.amazon.com.br/Effective-STL-Specific-Standard-Template/dp/0201749629/ref=pd_day0_14_24?_encoding=UTF8&pd_rd_i=0201749629&pd_rd_r=3c78913f-2d33-4f25-946b-9f02b03e273e&pd_rd_w=w0mzy&pd_rd_wg=3bL6K&pf_rd_p=c4c4ce2a-5c19-402b-95c2-78b460af9127&pf_rd_r=WYY9E2E4CC6DXHS6XTX1&psc=1&refRID=WYY9E2E4CC6DXHS6XTX1), Scott Meyers
- [C++ Concurrency in Action: Practical Multithreading](https://www.amazon.com.br/dp/1933988770/?coliid=IFWSZMV9BOYXG&colid=1EQTD27MP9O7E&psc=1&ref_=lv_ov_lig_dp_it), Anthony Williams
- [C++ in One Hour a Day, Sams Teach Yourself](https://www.amazon.com.br/One-Hour-Sams-Teach-Yourself/dp/0789757745/ref=pd_day0_14_9?_encoding=UTF8&pd_rd_i=0789757745&pd_rd_r=3c78913f-2d33-4f25-946b-9f02b03e273e&pd_rd_w=w0mzy&pd_rd_wg=3bL6K&pf_rd_p=c4c4ce2a-5c19-402b-95c2-78b460af9127&pf_rd_r=WYY9E2E4CC6DXHS6XTX1&psc=1&refRID=WYY9E2E4CC6DXHS6XTX1), Siddhartha Rao
- [Professional CMake: A Practical Guide](https://crascit.com/professional-cmake/), Craig Scott

### Programming in general

- [From Mathematics to Generic Programming](https://www.amazon.com.br/Mathematics-Generic-Programming-English-ebook/dp/B00PKH9XAG/ref=sr_1_1?__mk_pt_BR=%C3%85M%C3%85%C5%BD%C3%95%C3%91&dchild=1&keywords=generic+programming&qid=1597129117&sr=8-1), Alexander A. Stepanov
- [Clean Code](https://www.amazon.com.br/Clean-Code-Handbook-Software-Craftsmanship/dp/0132350882/ref=pd_day0_14_13?_encoding=UTF8&pd_rd_i=0132350882&pd_rd_r=3c78913f-2d33-4f25-946b-9f02b03e273e&pd_rd_w=w0mzy&pd_rd_wg=3bL6K&pf_rd_p=c4c4ce2a-5c19-402b-95c2-78b460af9127&pf_rd_r=WYY9E2E4CC6DXHS6XTX1&psc=1&refRID=WYY9E2E4CC6DXHS6XTX1), Robert C. Martin (Uncle Bob)
- [Clean Architecture](https://www.amazon.com.br/Clean-Architecture-Craftsmans-Software-Structure/dp/0134494164/ref=pd_bxgy_img_2/130-2934139-4618003?_encoding=UTF8&pd_rd_i=0134494164&pd_rd_r=07491272-a6d1-47bc-a4e3-32d9115de12e&pd_rd_w=9Qpx4&pd_rd_wg=JkbWa&pf_rd_p=cfb8196f-900f-4d57-8879-02619d5aab28&pf_rd_r=024KJ9B8B0K10JP0MFSS&psc=1&refRID=024KJ9B8B0K10JP0MFSS), Robert C. Martin (Uncle Bob)
- [The Clean Coder](https://www.amazon.com.br/Clean-Coder-Conduct-Professional-Programmers-ebook/dp/B0050JLC9Y/ref=sr_1_2?__mk_pt_BR=%C3%85M%C3%85%C5%BD%C3%95%C3%91&dchild=1&keywords=the+clean+coder&qid=1597129738&sr=8-2), Robert C. Martin (Uncle Bob)
- [The Linux Programming Interface](https://www.amazon.com.br/dp/B004OEJMZM/?coliid=I22USYQUBZ5ZKT&colid=1EQTD27MP9O7E&psc=0&ref_=lv_ov_lig_dp_it), Michael Kerrisk
- [Design Patterns: Elements of Reusable Object-Oriented Software](https://www.amazon.com.br/Design-Patterns-Elements-Reusable-Object-Oriented/dp/0201633612/ref=pd_day0_14_8?_encoding=UTF8&pd_rd_i=0201633612&pd_rd_r=3c78913f-2d33-4f25-946b-9f02b03e273e&pd_rd_w=w0mzy&pd_rd_wg=3bL6K&pf_rd_p=c4c4ce2a-5c19-402b-95c2-78b460af9127&pf_rd_r=WYY9E2E4CC6DXHS6XTX1&psc=1&refRID=WYY9E2E4CC6DXHS6XTX1), Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides (Gang of Four - GoF)
- [The Legacy Code Programmer's Toolbox](https://www.amazon.com.br/Legacy-Code-Programmers-Toolbox-Developers-ebook/dp/B07Y6T2VN1/ref=sr_1_2?__mk_pt_BR=%C3%85M%C3%85%C5%BD%C3%95%C3%91&dchild=1&keywords=legacy+code&qid=1597129805&sr=8-2), Jonathan Boccara
- [14 Habits of Highly Productive Developers](https://www.amazon.com.br/Habits-Highly-Productive-Developers-English-ebook/dp/B08BF74RRG/ref=sr_1_2?__mk_pt_BR=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=2651PS79GERI3&dchild=1&keywords=14+habitos+de+desenvolvedores+altamente+produtivos&qid=1597154480&sprefix=14+ha%2Caps%2C294&sr=8-2), Zeno Rocha
- [The Pragmatic Programmer](https://www.amazon.com.br/Pragmatic-Programmer-journey-mastery-Anniversary-ebook/dp/B07VRS84D1/ref=sr_1_1?__mk_pt_BR=%C3%85M%C3%85%C5%BD%C3%95%C3%91&dchild=1&keywords=The+Pragmatic+Programmer%3A+20th+Anniversary+Edition%2C+2nd+Edition&qid=1600100218&sr=8-1), David Thomas, Andrew Hunt
- [Working Effectively with Legacy Code](https://www.amazon.com.br/Working-Effectively-Legacy-Michael-Feathers/dp/0131177052), Michael Feathers
- [Soft Skills: The Software Developer’s Life Manual](https://www.amazon.com.br/Soft-Skills-Software-Developers-Manual/dp/1617292397), John Sonmez
- [The Self-Taught Programmer: The Definitive Guide to Programming Professionally](https://www.amazon.com.br/Self-Taught-Programmer-Definitive-Programming-Professionally-ebook/dp/B01M01YDQA), Cory Althoff

### Links

- [The World Map of C++ STL Algorithms](https://www.fluentcpp.com/getthemap/)
- [Design Patterns](https://refactoring.guru/design-patterns)
- [S.O.L.I.D Principles in Pictures](https://medium.com/backticks-tildes/the-s-o-l-i-d-principles-in-pictures-b34ce2f1e898)
- [Modern C++ Template Starter](https://github.com/TheLartians/ModernCppStarter)
- [Modern CMake Practices](https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/)
- [Awesome Cpp Libraries](https://github.com/fffaraz/awesome-cpp)
- [Awesome Hpp Libraries](https://github.com/p-ranav/awesome-hpp)
- [Backend Roadmap](https://roadmap.sh/backend)
- [40 maps that explain the internet](https://www.vox.com/a/internet-maps)
- [C++ Rule of Zero](http://web.archive.org/web/20171203020717/https://blog.rmf.io/cxx11/rule-of-zero)
- [Principles of Chaos Engineering](https://principlesofchaos.org/)
- [Big-O Cheat Sheet](https://www.bigocheatsheet.com/)

### Projects

- [CRUD with Django + PostgreQL](https://bezkoder.com/django-postgresql-crud-rest-framework/)

### Tools - Online Compilers

- [Godbolt Online Explorer](https://godbolt.org/), Online Compile Explorer

### Tools - CI

- [Travis](https://travis-ci.com), CI Tool
- [Appveyor](https://ci.appveyor.com), CI Tool
- [Jenkins](https://www.jenkins.io/), CI Tool

### Tools - Code Quality

- [Code Climate](https://codeclimate.com/), Quality Results
- [CodeFactor](https://www.codefactor.io), Code Quality
- [Codacy](https://app.codacy.com), Code Quality
- [Cppcheck](http://cppcheck.sourceforge.net/), Code Quality

### Tools - Code Coverage

- [Codecov](https://codecov.io/), Code Coverage
- [Coveralls](https://coveralls.io), Code Coverage
- [Sonarqube](https://www.sonarqube.org/), Code Coverage

### Tools - Code Documentation

- [Codedocs](https://codedocs.xyz/), Code Documentation
- [Doxygen](https://www.doxygen.nl/index.html), Code Documentation

### Tools - Sanitizers

- [Valgrind](https://valgrind.org/), Sanitizer
- [Google Sanitizer](https://github.com/google/sanitizers), Sanitizer

### Tools - Other

- [Robot Framework](https://robotframework.org/), Automation Framework (great for functional tests)
- [Grafana](https://grafana.com/), Metrics Visualization

## Либы для работы с сетью из С++

### Только синхронные либы

- **cpp-httplib**

### Асинхронные с поддержкой HTTP/REST API:

- **libcurl**
- **POCO**
- **Boost.Asio** (с поддержкой HTTP через Boost.Beast)
- **cpprestsdk**
- **Restinio**
- **Beast**
- **cpr**
- **crow**
- **Pistache**

### Асинхронные Вебсокеты:

- **libwebsockets**
- **websocketpp**
- **uWebSockets**

### Легковесные Асинхронные HTTP-серверы:

- **libmicrohttpd**
- **libmongoose**
- **libhttpserver**

### Асинхронные с поддержкой событийного цикла:

- **libevent**
- **libuv**

### Асинхронные - с поддержкой HTTP/2:

- **libhttp2**

## Modern Dependency Walker

- https://github.com/lucasg/Dependencies
- Создать новый раздел в README.md под названием Debugging Tools
