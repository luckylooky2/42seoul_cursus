# 42seoul_cursus

<꼭 알아야 할 cs지식>

-const 예약어\
=(const char *s)와 (char * const)의 차이점
∘const char ary[] = “hello”;
  char const ary[] = “hello”;
 -역참조를 통해서 값을 바꿀 수 없음
  하지만, 포인터 연산(ptr++;)은 가능(포인터를 움직일 수 있음)
  ※ptr[i]처럼 인덱스를 통해 값을 참조하는 것은 상관없음.
 -char *ptr = a;
  ptr을 통해서 a의 원소를 바꿀 수 있음(Warning이 발생하는 이유)
  const char *ptr = a; 로 해결할 수 있음(같은 자료형으로 캐스팅)

∘char * const ptr = ary;
-역참조를 통해 값을 바꿀 수 있음(?)
 하지만, 포인터 연산(ptr++;)은 불가능

-size_t

-memory 관련 함수들
=1 byte씩 이동하는데, 왜 캐스팅을 (char *)가 아닌 (unsigned char *)로 하는가?
∘캐스팅을 하는 이유
-(void *)로 받은 데이터를 몇 byte로 읽을 것인가 컴파일러가 알아야하기 때문

∘읽을 데이터가 음수일 수도 있는지(char *, 7비트), 음수가 아니어야 하는지(unsigned char *, 8비트)를 구분해야하기 때문

∘내부적으로 ascii 코드 이외의 값들은 linux에서 표시될 수 없게 처리한 것?
-printf(“%c”, 128;-123) 등을 해도 아무런 출력이 되지 않음

∘결론:
-어차피 char에 해당하는 byte만큼 복사하는 것은 맞음(이거는 문제가 아님)
-그래서 (char *)이나 (unsigned char*)이나 아무거나 해도 상관없을 듯(애초에 같은 byte만큼 붙여오기 때문)
-하지만, 관례적으로 unsigned가 쓰이고 있다는 점, 부호(7 vs 8 데이터비트로 인해 오류?가 발생할 수도 있다는 점), unsigned는 0이 유효한데, char는 0이 terminating character로 쓰인다는 점으로 unsigned 사용

∘그 이전에 char가 8비트인지의 문제도 살펴볼 필요가 있음(dolee님)
-1. Memset, memcpy 등의 함수는 이름과 같이 메모리의 정보 그대로를 복사하는 함수입니다. 그 메모리가 나타내는 값(value)을 복사하는 게 아니라 메모리의 비트열을 그대로 복사하는 것이 목적인 굉장히 저수준(low-level)의 목적을 가진 함수이죠. C 명세서에서는 이런 오브젝트의 비트열을 object representation 이라고 합니다. C에서의 오브젝트란 할당된 공간에 유의미한 값이 들어있는 것입니다. 쉽게 보면 변수를 메모리적인 관점에서 본 것이라고 이해해도 될 것 같습니다. 이제 메모리의 데이터를 복사하는 것이란 이 object representation을 복사하는 것이라는 것을 알 수 있습니다. Object representation이 곧 메모리의 비트열이기 때문이죠. 그런데 c명세서에서 object representation을 정의할 때 이렇게 정의하고 있습니다. "모든 n바이트의 객체는 unsigned char[n] 형태의 메모리에 복사 가능헤야 하며 이 때 그 비트열을 object representation이라고 정의한다". 이렇듯 그 정의 자체가 unsigned char에 의존하기 때문에 메모리 관련 함수에는 unsigned char를 사용합니다.
-2. C언어 명세서에서 바이트가 항상 8비트를 의미하지는 않습니다. C언어에서 바이트와 char는 서로 비교하기 좋으니 같이 이야기하겠습니다. 우선 명세 상 바이트는 "addressable unit 이며 시스템의 default character set을 저장할 수 있어야 한다" 라고 정의되며, 자료형의 char타입을 설명한 절에서 char는 "시스템의 default characrer set을 저장할 수 있어야 하며 그 동작은 signed char 혹은 unsigned char와 동일해야 한다. 다만 그 선택은 컴파일러 구현체의 자유이다" 라고 정의됩니다. 여기에서 바이트가 꼭 8비트여야 하는 것이 아니라 default character set을 저장할 수 있으며 addressable unit이기만 하면 된다는 것을 알 수 있습니다. 그리고 char는 거의 동일한 정의에서 addressable unit만 빠져있다는 것도 알 수 있죠. 이제 중간과정을 조금 생략해서, 명세서에 "바이트와 char는 동일하다" 라는 명시적 언급은 없지만 여러 조항들을 종합해보면 바이트와 char는 같은 사이즈임을 추론할 수 있습니다. 결국 char가 16비트인 시스템에서는 16비트가 1바이트가 되는 것이죠.
-3. 다시 이어서 바이트와 char에 대한 이야기를 이어가자면, c언어 명세서에는 CHAR_BIT 라는 것을 정의하는데요, 이름대로 char 의 크기를 비트수로 나타낸 것입니다. Char가 8비크라면 CHAR_BIT는 8이 되고 CHAR가 16비트라면 CHAR_BIT는 16이 되는 식이지요. 그리고 C 명세 상 바이트가 CHAR_BIT와 동일하다는 명시적 언급은 없는 것으로 알고 있는데 여러 조항들을 조합하면 결국 바이트의 크기가 CHAR_BIT와 동일하다는 결론을 추론할 수 있다고 합니다. 그리고 CHAR_BIT 의 예시를 8비트로 서술하며 "모든 구현체에서 CHAR_BIT의 크기는 이보다 커야 한다" 라고 기술하고 있습니다. 이 부분이 우리가 흔히 알고 있는 "char 형은 크기가 8비트 이상이어야 한다" 라는 주장의 근거로 쓰이는 명세입니다.
-4. 추가로 재밌는 것이 위의 char와 마찬가지로 모든 자료형이 보장해야 하는 최소범위에 대한 명세는 자료형을 설명하는 장에 없습니다. <limits.h> 를 정의하는 절에서 CHAR_MAX, INT_MIN 등을 정의하면서 숫자도 하나씩 같이 써 주고 "모든 컴파일러 구현체들은 이 수의 절대값보다 큰 수로 limits.h의 매크로들을 정의해야 한다" 라고 기술함으로써 각 자료형의 최소범위를 정의합니다.
-5. C언어의 공식 명세서는 유료이며 저작권으로 보호받기에 인터넷에서 구할 수 없습니다. 하지만 공식 명세서로 출판되기 전의 수정 단계에 있는 draft 버전을 무료로 공개해 줍니다. 인터넷에서 보는 대부분의 c 명세서는 이 draft버전일 겁니다. 제가 쓴 글도 c99의 draft를 기반으로 하고 있습니다. C11에서는 변경된 내용이 있을 수도 있습니다. 그래도 최종 draft는 거의 확정되기 직전 단계이기 때문에 최종 표준안과 크게 다른 부분은 앖을 겁니다. 그래서 대부분의 스택오버플로우 답변, 위키피디아 등에서도 draft를 출처로 사용합니다.“
-memset에서 초기화 가능한 인자는?
∘목적: 동일한 인자로 초기화하기 위해서
-1(0x1111...), 0(0x0000...) 이외의 0xababab..형식
-1은 (0x0...0001)이기 때문에 0xababab..형식이 아님 -> 전부 다른 값으로 대입

-왜 ascii(char)이 아니라 int로 파라미터를 받는가?
=isOOO를 비롯한 여러 함수들
∘int c; unsigned char ch = c; 가능한 이유
-리틀 엔디안 방식이기 때문
-0x12345678 -> 78 56 34 12로 표현되기 때문에 첫 번째 byte를 복사함

-ft_memcmp에서 특정 구간에서 –1, 1이 반환되는 이유/구현
∘일단, 반드시 (unsigned char *)로 캐스팅해줘야 함
-why? 뺄셈 연산 작업 때문에
int c[] = {12, 121, 2, 3};
int d[] = {-2, -112412, 2, 3};
printf("%d\n", memcmp(c, d, 7)); //음수(-1 or –242)  
printf("%d\n", ft_memcmp(c, d, 7)); //양수(14)

∘다르게 반환되는 이유?

-ft_strlcat
∘return: dest_len과 size를 비교한 후, (작은 것 + src_len)을 반환

∘왜 작은 것을, 그리고 전체를 반환? (linux man page)
-“strlcpy와 strlcat 함수는 생성하려고 시도한 문자열의 전체 길이를 반환합니다. 이것이 다소 혼란스럽게 보일 수 있지만, 절단 감지를 간단하게 하기 위해 수행되었습니다.”
-size < dest_len인 경우, 전부 다 복사하지 못하므로 return이 줄어듦 

-ft_strlen
∘인자가 (null) 포인터일 경우: Segmentation fault가 발생
  인자가 빈 문자열(“”)일 경우: 0을 반환
 -why? (null) 포인터는 존재하지 않는(셀 수 없는) 것을 세려고하기 때문.
 -그래서, 실제에서 사용할 때, 널 가드를 해주는 것이 보통
 -int someStrLen;
  if (someStr != NULL)  // or if (someStr)
  	someStrLen = strlen(someStr);
  else
    // handle error.
