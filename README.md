# debug dll
dllmain.cpp을 적당히 수정하고 빌드한 뒤 디버깅할 프로세스에 dll을 삽입하면 됩니다.
마이크로소프트의 Detours를 이용해 인라인 함수 후킹 방식으로 구현했습니다.

아래는 dll 인젝터 다운로드 링크입니다.
https://github.com/DarthTon/Xenos/releases/tag/2.3.2