#include <stdio.h>
#include <unistd.h>
#include <sys/perm.h>
#include <sys/io.h>

unsigned char read_cmos(unsigned char index) {  // CMOS로부터 정보를 읽는 함수 정의
    unsigned char value;                        // CMOS로부터 읽은 값을 저장할 변수 선언
    outb(index, 0x70);                          // CMOS 주소 포트(0x70)에 인덱스 값을 쓰기
    usleep(100);                                // 100 마이크로초 동안 대기 (CMOS I/O에 시간이 필요함)
    value = inb(0x71);                          // CMOS 데이터 포트(0x71)에서 값을 읽기
    return value;                               // 읽은 값을 반환
}

int main() {
    int ret;
    ret = iopl(3);

    if (ret != 0) {
        fprintf(stderr, "ret: %d\n", ret);
        return ret;
    }

    // CMOS로부터 시간 정보 읽기
    unsigned char cmos_seconds = read_cmos(0x00); // CMOS에서 초 값을 읽음
    unsigned char cmos_minutes = read_cmos(0x02); // CMOS에서 분 값을 읽음
    unsigned char cmos_hours   = read_cmos(0x04); // CMOS에서 시 값을 읽음

    // CMOS 시간 출력
    printf("현재 CMOS 시간: %02x시 %02x분 %02x초\n", cmos_hours, cmos_minutes, cmos_seconds);
}

