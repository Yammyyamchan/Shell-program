# 간단한 쉘 프로그램

_1. 기존의 shell과 유사하게 무한 loop를 돌면서, 사용자의 명령을 입력받는다._

_2. 사용자의 명령이 PATH에 저장된 경로에 존재하는지 검사하고, 입력 받은 명령을 child프로세스가 실행하도록 한다._


---
![스크린샷 2023-12-29 10-38-39](https://github.com/Yammyyamchan/Shell-program/assets/131407815/546fc7f8-1160-4088-b938-74e6e0b667c8)

-cd문자열이 입력되면, chdir()함수를 이용해 경로를 바꿈.

-myshell을 실행시키면 처음에 홈 디렉터리에서 시작할 수 있게 chdir()함수를 이용함.

-getcwd()함수를 이용해 현재 디렉터리 위치를 얻고, 파란색으로 바꿔서 출력시킴.

---
![스크린샷 2023-12-29 10-39-37](https://github.com/Yammyyamchan/Shell-program/assets/131407815/5a22329f-fe29-4a3b-b7b5-bcdb95347260)

-시그널이 발생해도, 쉘이 종료되지 않도록 시그널처리함수를 만듬.

---

![스크린샷 2023-12-29 10-40-47](https://github.com/Yammyyamchan/Shell-program/assets/131407815/5a333b7c-d986-49af-8f57-b3ef88b85ccb)

-사용자 명령이 PATH에 저장되어 있는 경로에 존재하는지 access()함수를 이용해 판단.

-존재하면 sprintf()함수를 이용해 맨 앞 명령어에 경로를 붙여서 저장함.

-자식 프로세스를 생성하고, execv()함수를 호출해서 명령을 실행시킴.

---
![스크린샷 2023-12-29 10-50-14](https://github.com/Yammyyamchan/Shell-program/assets/131407815/430af026-0805-49c6-bf0a-ce4fe80e0267)

-사용자가 입력한 명령에 "|"가 있는지 strcmp()를 이용해 확인하고, 존재하면 자식프로세스를 생성.

-dup()와 close()을 이용해 입출력을 다시 재정의함.

-execvp()호출을 통해 파이프 명령 구현.

\* 아직 파이프를 하나만 사용할 수 있게 구현했음. 다음에 2개 이상 사용할 수 있도록 수정할 예정임.\*