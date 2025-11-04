#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cjson/cJSON.h>

#define MAX_STR 256

ssize_t read_line(int sockfd, char *buffer, size_t max_len) {
    ssize_t total_read = 0;
    char ch;
    while (total_read < max_len - 1) {
        ssize_t bytes = recv(sockfd, &ch, 1, 0);
        if (bytes <= 0) {
            if (total_read == 0)
                return -1;
            break;
        }
        if (ch == '\n')
            break;
        buffer[total_read++] = ch;
    }
    buffer[total_read] = '\0';
    return total_read;
}

int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: %s <server_ip> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char *server_ip = argv[1];
    int port = atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if(inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    char abnormal_cause[MAX_STR];
    char abnormal_discerned_timestamp_str[MAX_STR];
    int abnormal_discerned_timestamp;
    
    char scenario_causative_object_str[MAX_STR];
    int scenario_causative_object;
    char scenario_description[MAX_STR];
    char scenario_id_str[MAX_STR];
    int scenario_id;
    
    char date_time_str[MAX_STR];
    int date_time;
    char driving_mode_str[MAX_STR];
    int driving_mode;
    
/*    char duration_str[MAX_STR];
    int duration;
    char record_date[MAX_STR];
    char topic_name[MAX_STR];
    char topic_type[MAX_STR];*/
    
//    char dynamic_elements[MAX_STR];
    char illuminance_str[MAX_STR];
    int illuminance;
    char rainfall_str[MAX_STR];
    int rainfall;
    char cloudness_str[MAX_STR];
    int cloudness;
    char snowfall_str[MAX_STR];
    int snowfall;
    char wind_str[MAX_STR];
    int wind;
//    char scenary[MAX_STR];
    
/*    char image[MAX_STR];
    char travel_path[MAX_STR];
    char idx_str[MAX_STR];
    int idx;
    char latitude[MAX_STR];
    int latitude;
    char longitude[MAX_STR];
    int longitude;
    char video[MAX_STR];*/
    
    char triggered_cause_str[MAX_STR];
    int triggered_cause;
//    char triggered_time[MAX_STR];
    
    if(read_line(sockfd, abnormal_cause, MAX_STR) < 0) {
        fprintf(stderr, "Error reading abnormal_cause\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    if(read_line(sockfd, abnormal_discerned_timestamp_str, MAX_STR) < 0) {
        fprintf(stderr, "Error reading abnormal_discerned_timestamp\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    abnormal_discerned_timestamp = atoi(abnormal_discerned_timestamp_str);
    
    if(read_line(sockfd, scenario_causative_object_str, MAX_STR) < 0) {
        fprintf(stderr, "Error reading scenario_causative_object\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    scenario_causative_object = atoi(scenario_causative_object_str);
    
    if(read_line(sockfd, scenario_description, MAX_STR) < 0) {
        fprintf(stderr, "Error reading scenario_description\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    if(read_line(sockfd, scenario_id_str, MAX_STR) < 0) {
        fprintf(stderr, "Error reading scenario_id\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    scenario_id = atoi(scenario_id_str);
    
    if(read_line(sockfd, date_time_str, MAX_STR) < 0) {
        fprintf(stderr, "Error reading date_time\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    date_time = atoi(date_time_str);
    
    if(read_line(sockfd, driving_mode_str, MAX_STR) < 0) {
        fprintf(stderr, "Error reading driving_mode\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    driving_mode = atoi(driving_mode_str);
    
/*    if(read_line(sockfd, dynamic_elements, MAX_STR) < 0) {
        fprintf(stderr, "Error reading dynamic_elements\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }*/
    
    if(read_line(sockfd, illuminance_str, MAX_STR) < 0) {
        fprintf(stderr, "Error reading illuminance\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    illuminance = atoi(illuminance_str);
    
    if(read_line(sockfd, rainfall_str, MAX_STR) < 0) {
        fprintf(stderr, "Error reading rainfall\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    rainfall = atoi(rainfall_str);
    
    if(read_line(sockfd, cloudness_str, MAX_STR) < 0) {
        fprintf(stderr, "Error reading cloudness\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    cloudness = atoi(cloudness_str);
    
    if(read_line(sockfd, snowfall_str, MAX_STR) < 0) {
        fprintf(stderr, "Error reading snowfall\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    snowfall = atoi(snowfall_str);
    
    if(read_line(sockfd, wind_str, MAX_STR) < 0) {
        fprintf(stderr, "Error reading wind\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    wind = atoi(wind_str);
    
/*    if(read_line(sockfd, scenary, MAX_STR) < 0) {
        fprintf(stderr, "Error reading scenary\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }*/
    
/*    if(read_line(sockfd, image, MAX_STR) < 0) {
        fprintf(stderr, "Error reading image\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    if(read_line(sockfd, travel_path, MAX_STR) < 0) {
        fprintf(stderr, "Error reading travel_path\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    if(read_line(sockfd, idx_str, MAX_STR) < 0) {
        fprintf(stderr, "Error reading idx\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    idx = atoi(idx_str);
    
    if(read_line(sockfd, latitude_str, MAX_STR) < 0) {
        fprintf(stderr, "Error reading latitude\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    latitude = atoi(latitude_str);
    
    if(read_line(sockfd, longitude_str, MAX_STR) < 0) {
        fprintf(stderr, "Error reading longitude\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    longitude = atoi(longitude_str);
    
    if(read_line(sockfd, video, MAX_STR) < 0) {
        fprintf(stderr, "Error reading video\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }*/
    
    if(read_line(sockfd, triggered_cause_str, MAX_STR) < 0) {
        fprintf(stderr, "Error reading triggered_cause\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    triggered_cause = atoi(triggered_cause_str);
    
    char chat_data[] = "receive data";
    if (write(sockfd, chat_data, strlen(chat_data)) < 0) {
        perror("Write failed");
    }
    
    // 수신 완료 후 소켓 닫기
    close(sockfd);
    
    // 수신한 값으로 JSON 객체 생성 (cJSON 이용)
    cJSON *root = cJSON_CreateObject();

    // abnormal_driving_cause 객체 생성
    cJSON *abnormal_driving_cause_obj = cJSON_CreateObject();
    cJSON_AddStringToObject(abnormal_driving_cause_obj, "cause", abnormal_cause);
    cJSON_AddNumberToObject(abnormal_driving_cause_obj, "discerned_timestamp", abnormal_discerned_timestamp);

    cJSON *scenario_obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(scenario_obj, "causative_object", scenario_causative_object);
    cJSON_AddStringToObject(scenario_obj, "description", scenario_description);
    cJSON_AddNumberToObject(scenario_obj, "scenario_id", scenario_id);

    // "sceanrio" 키로 scenario 객체 추가
    cJSON_AddItemToObject(abnormal_driving_cause_obj, "sceanrio", scenario_obj);
    cJSON_AddItemToObject(root, "abnormal_driving_cause", abnormal_driving_cause_obj);

    // date_time와 driving_mode 추가
    cJSON_AddNumberToObject(root, "date_time", date_time);
    cJSON_AddNumberToObject(root, "driving_mode", driving_mode);

    // log_header
/*    cJSON *log_header_obj = cJSON_CreateObject();
    cJSON *topic_list_obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(log_header_obj, "duration", duration);
    cJSON_AddStringToObject(log_header_obj, "record_date", record_date);
    cJSON_AddStringToObject(topic_list_obj, "topic_name", topic_name);
    cJSON_AddStringToObject(topic_list_obj, "topic_type", topic_type);
    cJSON_AddItemToObject(log_header_obj, "topic_list", topic_list_obj);
    cJSON_AddItemToObject(root, "log_header", log_header_obj);*/

    // environmental_conditions
    cJSON *scene_context_obj = cJSON_CreateObject();
    cJSON *environmental_conditions_obj = cJSON_CreateObject();
//    cJSON_AddStringToObject(scene_context_obj, "dynamic_elements", dynamic_elements);
    cJSON_AddNumberToObject(environmental_conditions_obj, "illuminance", illuminance);
    cJSON_AddNumberToObject(environmental_conditions_obj, "rainfall", rainfall);
    cJSON_AddNumberToObject(environmental_conditions_obj, "cloudness", cloudness);
    cJSON_AddNumberToObject(environmental_conditions_obj, "snowfall", snowfall);
    cJSON_AddNumberToObject(environmental_conditions_obj, "wind", wind);
//    cJSON_AddStringToObject(scene_context_obj, "scenary", scenary);
    cJSON_AddItemToObject(scene_context_obj, "environmental_conditions", environmental_conditions_obj);
    cJSON_AddItemToObject(root, "scene_context", scene_context_obj);

    // screen
/*    cJSON *screen_obj = cJSON_CreateObject();
    cJSON *triggered_position_obj = cJSON_CreateObject();
    cJSON_AddStringToObject(screen_obj, "image", image);
    cJSON_AddStringToObject(screen_obj, "travel_path", travel_path);
    cJSON_AddNumberToObject(triggered_position_obj, "idx", idx);
    cJSON_AddNumberToObject(triggered_position_obj, "latitude", latitude);
    cJSON_AddNumberToObject(triggered_position_obj, "longitude", longitude);
    cJSON_AddStringToObject(screen_obj, "video", video);
    cJSON_AddItemToObject(screen_obj, "triggered_position", triggered_position_obj);
    cJSON_AddItemToObject(root, "screen", screen_obj);*/

    // triggered_cause 객체 생성
    cJSON *triggered_cause_obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(triggered_cause_obj, "cause", triggered_cause);
//    cJSON_AddStringToObject(triggered_cause_obj, "triggered_time", triggered_time);
    cJSON_AddItemToObject(root, "triggered_cause", triggered_cause_obj);

    // JSON 파일로 저장
    char *json_string = cJSON_Print(root);
    FILE *file = fopen("meta.json", "w"); // triggered_time 불러와서 타임스탬프_세션ID_meta.json으로 수정 필요
    if(file) {
        fprintf(file, "%s\n", json_string);
        fclose(file);
        printf("JSON 파일 생성 완료: meta.json\n");
    } else {
        printf("파일 생성 실패!\n");
    }

    free(json_string);
    cJSON_Delete(root);

    return 0;
}

