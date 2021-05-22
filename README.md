# Real-Time Wireless EKG Monitoring & Feedback System
=============
> For Capstone Design


[ 1. 주제선정 및 배경 ]
- 기존의 외래환자는 외부에서 사용하기 힘든 hardwired system이 요구되거나, 간편한 EKG Monitoring System을 이용하더라도 delay가 존재하여 응급상황 발생시 epinephrine 또는 lidocaine 투여와 같은 적절한 first-line treatments가 취해지기 어려운 문제가 있음
- 외부에서 사용하기 편하면서도 delay를 최소화하여 심질환 환자의 응급상황 발생시 적절한 first-line treatments가 이루어지게 하므로서 환자의 생존률을 높이고자함
- 이를 위해 'Real-Time Wireless EKG Monitoring & Feedback System'을 개발하고자 함

[ 2. 개발 목표 ]
- 저지연, 저전력, 저비용, 실시간성, 광범위성을 확보하기 위한 적절한 Network 선정

|Network|Compatibility|
|:---|:---|
|`WBANs & WPANs`|1|
|`WLANs`|2|
|`Cellular`|3|
|`LTE-MTC`|4|

- 원내환자와 비교했을 때 원내환자의 EKG Data 역시 최소한의 Quality를 유지해야함

-------------
### Quectel BG96
<img src="/Img/bg96.png">

### Arduino MEGA2560 / Quectel BG96 / AD8232
<img src="/Img/product.jpg">

> Development resource, Arduino library and example code for LTE-Cat.m1 module produced by CodeZoo   
> [ https://github.com/codezoo-ltd/CodeZoo_CATM1_Arduino ]

### Server
- Ubuntu 18.04.5 LTS   
- mysql : Ver 15.1 Distrib 10.5.10-MariaDB, for debian-linux-gnu (x86_64) using readline 5.2   
- nodejs : node - v12.22.1, npm - 6.14.12   
