# debug dll
Bitblt 함수를 후킹해 함수 호출을 모니터링하는 예제 소스입니다.    
  
dllmain.cpp을 필요에 따라 적당히 수정하고 빌드한 뒤, 디버깅할 프로세스에 dll을 삽입하시면 됩니다.  
마이크로소프트에서 개발한 Detours 라이브러리를 이용해 인라인 함수 후킹 방식으로 구현했습니다.  
  
만약 라이브러리 함수가 아니라 사용자 정의 함수를 후킹해야 한다면,  
ORGFP originFunc = (ORGFP)((DWORD)GetModuleHandle(NULL) + 함수 오프셋);  
처럼 수정하시면 됩니다.  
  
아래는 dll 인젝터 다운로드 링크입니다.  
https://github.com/DarthTon/Xenos/releases/latest