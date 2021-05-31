# Real-Time Wireless EKG Monitoring & Feedback System
-------------
> For Capstone Design


[ 1. Backgrounds ]
- Currently, high-quality remote medical treatment for outpatients with heart disease requires hard-wired systems that are difficult to use outside, or there is a long latency problem in data transferring, even if there is an easy-to-use system.   
- Even in the event of an emergency due to this problem, proper first-line treatments such as epinephrine or lidocaine administration are difficult to take.   
- So, we plan to develop a real-time wireless EKG monitoring system that is easy to use outside while minimizing EKG data transfer latency.   
- Then, in the emergency situation, the patient's appropriate first-line treatment will be taken and survival rates will rise extremely.

[ 2. Development Goals ]
- Proper network selection for low-cost, low-power, continuous data, low-latency, wide-range : LTE-MTC   

|Network|Compatibility|
|:---|:---|
|`WBANs & WPANs`|1|
|`WLANs`|2|
|`Cellular`|3|
|`LTE-MTC`|4|

- Maintaining EKG data that ensures minimum quality for high-quality remote care for outpatients compared to in-hospital patients   

< 추가예정 >   
[ 3. 설계 및 제작과정 ]   
[ 4. 결과 및 분석 (시연) ]   
[ 5. 개선 및 발전 방향 ]   
[ 6. 참고문헌 ]   

-------------
### Arduino MEGA2560 / Quectel BG96 / AD8232
<img src="/Img/product.jpg">

> Development resource, Arduino library and example code for LTE-Cat.m1 module produced by CodeZoo   
> [ https://github.com/codezoo-ltd/CodeZoo_CATM1_Arduino ]

### Server
- Ubuntu 18.04.5 LTS   
- mysql : Ver 15.1 Distrib 10.5.10-MariaDB, for debian-linux-gnu (x86_64) using readline 5.2   
- nodejs : node - v12.22.1, npm - 6.14.12   
-------------
