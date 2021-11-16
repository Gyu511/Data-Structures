Reverce.c와 Convert.c는 주석으로 연결리스트버전과 배열버전을 구분했습니다. 헤더 주석이랑 메인주석 바꾸셔서 확인하시면됩니다.
Calculator.c는 연결리스트버전으로 Stack_Link2.h와 Calculator_arr.c는 배열버전으로 Stack_Array2.h와 실행시키시면 됩니다.
그리고 Calculator_arr.c에 105번줄에 typedef int Element;로 자료형 변환해줬는데 결과는 잘 나오는데 변환이 안된것처럼 워닝이 뜨는데 이유는 잘 모르겠습니다.