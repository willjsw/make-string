# make-string
## String 클래스를 Clang으로 구성해보는 연습 프로젝트

## 프로젝트 개요
- C 포인터/구조체를 활용한 String 클래스 구현
- String 메소드를 구현할 것(length, substring, append)
- AI를 사용하지 않을 것

## How to
**Linux & Mac**
```bash
# compile
gcc ./src/main.c -o ./build/main

#run
./build/main
```

**Window**
```bash
# compile
gcc ./src/main.c -o ./build/main.exe

#run
./build/main.exe
```

**참고한 사이트**
[C로 Class 억지로 만들기](https://cpattern.tistory.com/6)

[[Java] 자바 문자열을 다루는 String 클래스 메소드 총정리](https://hongong.hanbit.co.kr/java-%EC%9E%90%EB%B0%94-%EB%AC%B8%EC%9E%90%EC%97%B4%EC%9D%84-%EB%8B%A4%EB%A3%A8%EB%8A%94-string-%ED%81%B4%EB%9E%98%EC%8A%A4-%EB%A9%94%EC%86%8C%EB%93%9C-%EC%B4%9D%EC%A0%95%EB%A6%AC/)

[C언어로 클래스 구현해보기](https://sunwoo-psychiatric-ward.tistory.com/6)

## 코드리뷰 전 학습한 내용
- Java의 클래스를 완벽히 구현할 수는 없지만, C의 구조체를 활용해 모방해볼 수 있음
    - 구조체는 내부적으로 `가장 큰 자료형 byte수의 배수`로 나머지 모든 내부 멤버의 저장 공간을 할당함.
    - 따라서 가장 큰 자료형 -> 작은 자료형의 순서로 선언하는 것이 메모리 공간 절약에 유리함.(패딩 없애기)

- 스코프를 벗어나면 스택 상 메모리에 저장된 값의 불변성을 보장할 수 없음
    - 함수 Call이 끝나면, 스택 포인터는 다시 이전 스택프레임을 가리키게 된다.
    - 이 때문에 내부에서 지역변수를 선언해 return 해도 스택 영역에 남아있게 됨 -> Dangling Pointer
    - 이후 새로운 함수가 호출되어 스택프레임이 생성되면, 이 영역에 남아있던 값들은 새 값에 의해 덮어씌워지게 됨
    - malloc, calloc과 같은 메모리 동적 할당 함수, 또는 static 변수를 통해 힙이나 데이터 영역에 저장해야 함수 종료 이후에도 불변성이 보장된 데이터를 사용할 수 있음.

- 배열은 포인터다
    - `char *arr` 은 `char[0]`과 동일한 의미를 지님.
    - 배열의 인덱스: 배열 첫번쨰 메모리 주소에 char, int 등 지정한 자료형의 크기만큼, **[지정된 인덱스]** 번 이동시킬 수 있음.
    - ex) `int[2]` -> 시작 주소값에 64byte 시스템 기준 int형 크기(4byte)를 2번 더하는 효과
    - 동적으로 배열을 할당하고자 한다면, 일관된 자료형의 크기를 할당해야 함
    ```C
    int *mem = (int *)malloc(sizeof(tmp) + sizeof(int)); //(O)
    int *mem = (int *)malloc(sizeof(tmp) + 1); //(X) 타입 캐스팅 자동으로 되지 않음, 5Byte 할당
    ```
- 문자열(String)은 다음 두가지 조건을 만족시켜야 함
    - `char` 자료형으로 구성된 고정길이배열
    - 마지막이 `NULL` 또는 아스키문자 0(`\0`)으로 끝나는 char형 배열
    - 이 때문에 문자열을 위한 공간을 할당할 때에는, 실제 문자열의 크기보다 1byte를 더 할당해줘야 함

     ```C
    char *abcd = "abcd";
    char *new_abcd = (char *)malloc(sizeof(abcd) + 1); // 마지막 NULL 을 위한 추가 1byte
    ```
    
## 코드리뷰
### 라이브러리에서의 메모리관리는 라이브러리를 벗어나지 않도록 하자
- String 라이브러리 화, 동적할당/static 시, 햘댱 해제 권한은 라이브러리 안으로 편입시키는 것이 좋음
- delete(메모리해제)와 같은 함수를 라이브러리에 추가할 필요 있음

### "값 전달"과 "포인터 전달을 잘 구분하자
- Clang 의 데이터 전달 방식은 2가지
- 실제 데이터의 값을 그대로 모두 넘기면 C의 가장 큰 장점인 포인터를 통한 효율적인 데이터 조작을 활용하지 못할 수 있음
- 반드시 값을 복사해서 써야 하는 경우가 아니라면, 포인터를 활용

### 효율보다 중요한 건 코드의 명확성
- C/C++ 에서의 값 복사 -> "오로지 값만" 복사해야 함.
    - Value: 내가 가하는 조작이 다른 메모리에 전혀 영향이 없다.
	- Pointer: 현재 데이터에 가하는 조작이 사이드이펙트를 유발할 수 있다. or 해당 데이터는 의도와 다르게 조작될 수 있다.
- C/C++를 개발자는 포인터/값 반환 타입에 따라 해당 코드의 의미를 파악해야 함
    - Value: 복사된 데이터이므로, 개발자가 해당 데이터 및 구조체와 내부 변수를 자유롭게 수정할 수 있음
    - Pointer: 어딘가에 영향을 비칠 수 있기 때문에, 포인터로만 접근해서 사용해야 함.
- const 사용 
    - C90(ANSI C)부터 C에서도 `const` 키워드를 통해 상수 선언 가능해짐
    - 코드를 읽는 사람에게 해당 변수는 '임의로 조작해서는 안되는 값'이라는 의미를 전달
- 구조체 멤버와 변수의 구분
    - c 에서는 구조체와 변수 중, 어느것이 함수고 어느 것이 변수인지 구분하기 쉽지 않음
    - typedef를 활용한 함수포인터 별칭보다는,포인터의 선언을 그대로 적어주는 것이 더욱 명확함
    - 조작을 가할 수 있는 변수의 경우, 함수를 통해 동적으로 반환하기 보단 구조체의 멤버 변수로 지정해두자
    
    **기존 구조체**
    ```c
    typedef struct _String{
        char *head;
        Length length; 
        Append append;
        Substring substring;
        Replace replace;
    } String;
    ```

     **개선된 구조체**
    ```c
    typedef struct _String{
        char *head;
        int size; //조작을 가한 이후의 데이터는 명확하게 멤버로 추가
        void (*Append)(void *, char *);
        void (*Substring)(void *, int, int);
        void (*Replace)(void *, char *target, char *newstr);
        //내부에 선언된 함수 포인터의 경우도, 무조건 추가하는 것보다는 필요한 경우에만 넣는 것이 좋음
        //ex) 동일한 이름을 + 다른 동작을 하는 메서드를 "두개의 서로 다른 구조체 각각에 선언"하려고 하는 경우(상속 구현)
    } String;
    ```

### 종합
- 읽는 사람을 고려하는, 명확한 코드를 짜려고 하자.