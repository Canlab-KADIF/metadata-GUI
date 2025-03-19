# 컴파일러 및 옵션
CC = gcc
CFLAGS = -Wall -g

# 소스 파일 및 출력 실행파일 이름
CLIENT_SRC = client.c

CLIENT_BIN = gui_client

# 기본 타겟: 클라이언트 빌드
all: $(CLIENT_BIN)

# 클라이언트 빌드 (cJSON 라이브러리 링크)
$(CLIENT_BIN): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $@ $< -lcjson

# 클린 타겟: 빌드 결과 삭제
clean:
	rm -f $(CLIENT_BIN)
