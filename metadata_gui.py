import socket
import threading
import tkinter as tk
from tkinter import scrolledtext
from tkinter import ttk

class ServerApp:
    def __init__(self, master):
        self.master = master
        master.title("json 생성")

        self.clients = []  # 연결된 클라이언트 목록
        self.combobox_value = {}
        self.checkbox_value = {}
        self.textbox_value = {}

        # meta.json
        metajson = tk.LabelFrame(master, text="meta")
        metajson.pack(pady=10)
        etc_frame = tk.Frame(metajson)
        etc_frame.pack(pady=5)
        env_frame = tk.LabelFrame(metajson, text="environmental conditions")
        env_frame.pack(padx=10, pady=5)
        abnormal_frame = tk.LabelFrame(metajson, text="abnormal driving cause")
        abnormal_frame.pack(padx=10, pady=5)
        scenario_frame = tk.LabelFrame(abnormal_frame, text="scenario")
        scenario_frame.pack(padx=10, pady=5)

        self.datetime = ["Morning", "Afternoon", "Night"]
        self.driving_mode = ["Driver", "Automated System"]
        self.trigger_cause = ["None", "Take Over", "Sensor Failure", "System Failure", "Actuation Failure", "V2x Error", "Abrupt Maneuver"]
        self.cloudness = ["Clear", "Partly Cloudy", "Overcast"]
        self.intensity = ["None", "Light", "Moderate", "Heavy"]
        self.illuminance = ["Fully Daylight", "Partial Daylight", "Low Light"]
        self.scenario_id = ["scenario1", "scenario2", "scenario3"]
        self.abnormal_cause = ["cause1", "cause2", "cause3"]
        self.test = ["undecided", "decided"]

        self.combobox_create(self.datetime, etc_frame, "datetime", 9)
        self.combobox_create(self.driving_mode, etc_frame, "driving mode", 16)
        self.combobox_create(self.trigger_cause, etc_frame, "trigger cause", 15)

        self.combobox_create(self.cloudness, env_frame, "cloudness", 12)
        self.combobox_create(self.intensity, env_frame, "wind", 9)
        self.combobox_create(self.intensity, env_frame, "rainfall", 9)
        self.combobox_create(self.intensity, env_frame, "snowfall", 9)
        self.combobox_create(self.illuminance, env_frame, "illuminance", 13)

        self.combobox_create(self.scenario_id, scenario_frame, "scenario id", 10)
        self.combobox_create(self.test, scenario_frame, "causative object", 10)
        self.textbox_create(scenario_frame, "description", 35)
        self.combobox_create(self.abnormal_cause, abnormal_frame, "abnormal cause", 10)
        self.combobox_create(self.test, abnormal_frame, "discerned timestamp", 10)

        # route.json
        routejson = tk.LabelFrame(master, text="route")
        routejson.pack(pady=10)
        dynamic_frame = tk.LabelFrame(routejson, text="dynamic elements")
        dynamic_frame.pack(padx=10, pady=5)
        scenery_frame = tk.LabelFrame(routejson, text="scenery")
        scenery_frame.pack(padx=10, pady=5)
        junction_frame = tk.LabelFrame(scenery_frame, text="junctions")
        junction_frame.pack(padx=10, pady=5)
        travel_frame = tk.LabelFrame(routejson, text="travel path")
        travel_frame.pack(padx=10, pady=5)

        self.agent_density = ["Few", "Moderate", "Dense", "Unknown"]
        self.special_vehicles = ["Ambulance", "Police Vehicle", "Work Vehicle", "Traffic Management Vehicle", "Fire Appliance Vehicle"]
        self.intersections = ["None", "Protected", "Unprotected"]
        self.roundabouts = ["False", "True"]
        self.zones = ["None", "School Zone"]
        self.road_types = ["Highways", "Primary Roads", "Local Roads", "Parking"]
        self.special_structures = ["Automatic Access Control", "Bridges", "Crosswalk", "Rail Crossing", "Tunnels", "Toll Plaza"]

        self.combobox_create(self.agent_density, dynamic_frame, "pedestrian density", 9)
        self.combobox_create(self.agent_density, dynamic_frame, "traffic density", 9)
        self.checkbox_create(self.special_vehicles, dynamic_frame, "special vehicles")

        self.combobox_create(self.zones, scenery_frame, "zones", 11)
        self.combobox_create(self.road_types, scenery_frame, "road types", 13)
        self.combobox_create(self.intersections, junction_frame, "intersections", 11)
        self.combobox_create(self.roundabouts, junction_frame, "roundabouts", 6)
        self.checkbox_create(self.special_structures, scenery_frame, "special structures")

        # 스크롤 가능한 텍스트 영역
        self.text_area = scrolledtext.ScrolledText(master, wrap=tk.WORD, width=90, height=5)
        self.text_area.pack(padx=10, pady=10)

        # 전송 버튼 추가
        self.send_button = tk.Button(master, text="confirm", command=self.send_user_message)
        self.send_button.pack(pady=5)

        self.start_server()

    def start_server(self):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind(('127.0.0.1', 12346))
        self.server_socket.listen()

        self.accept_thread = threading.Thread(target=self.accept_connections, daemon=True)
        self.accept_thread.start()

    def accept_connections(self):
        while True:
            conn, addr = self.server_socket.accept()
            self.clients.append(conn)  # 클라이언트를 리스트에 추가
            self.text_area.insert(tk.END, f"{addr}가 연결되었습니다.\n")
            threading.Thread(target=self.handle_client, args=(conn,), daemon=True).start()

    def handle_client(self, conn):
        while True:
            try:
                data = conn.recv(1024)  # 클라이언트로부터 데이터 수신
                if not data:
                    break  # 데이터가 없으면 클라이언트가 연결을 종료한 것
                message = data.decode('utf-8')  # 데이터를 문자열로 디코딩
                # 클라이언트 메시지를 텍스트 영역에 출력
                self.text_area.insert(tk.END, f"클라이언트로부터 받은 메시지: {message}\n")
            except Exception as e:
                self.text_area.insert(tk.END, f"클라이언트 통신 오류: {e}\n")
                break

        conn.close()
        self.clients.remove(conn)  # 클라이언트가 연결을 끊으면 목록에서 제거

    def setup_message(self, items, title):
        return items.index(self.combobox_value[title])

    def setup_checkbox_message(self, title):
        selected_items = [var.get() for item, var in self.checkbox_value[title].items() if var.get() != ""]
        if not selected_items:
            return ""
        return "_".join(selected_items)

    def send_user_message(self):
        # meta.json
        abnormal_cause_send = self.setup_message(self.abnormal_cause, "abnormal cause")
        discerned_timestamp_send = self.setup_message(self.test, "discerned timestamp")
        causative_object_send = self.setup_message(self.test, "causative object")
        description_send = self.textbox_value["description"].get()
        scenario_id_send = self.setup_message(self.scenario_id, "scenario id")
        datetime_send = self.setup_message(self.datetime, "datetime")
        driving_mode_send = self.setup_message(self.driving_mode, "driving mode")
        illuminance_send = self.setup_message(self.illuminance, "illuminance")
        rainfall_send = self.setup_message(self.intensity, "rainfall")
        cloudness_send = self.setup_message(self.cloudness, "cloudness")
        snowfall_send = self.setup_message(self.intensity, "snowfall")
        wind_send = self.setup_message(self.intensity, "wind")
        trigger_cause_send = self.setup_message(self.trigger_cause, "trigger cause")

        # route.json
        pedestrian_density_send = self.setup_message(self.agent_density, "pedestrian density")
        traffic_density_send = self.setup_message(self.agent_density, "traffic density")
        special_vehicles_send = self.setup_checkbox_message("special vehicles")
        zones_send = self.setup_message(self.zones, "zones")
        road_types_send = self.setup_message(self.road_types, "road types")
        intersections_send = self.setup_message(self.intersections, "intersections")
        roundabouts_send = self.setup_message(self.roundabouts, "roundabouts")
        special_structures_send = self.setup_checkbox_message("special structures")

        message = f"{abnormal_cause_send}\n{discerned_timestamp_send}\n{causative_object_send}\n{description_send}\n{scenario_id_send}\n{datetime_send}\n{driving_mode_send}\n{illuminance_send}\n{rainfall_send}\n{cloudness_send}\n{snowfall_send}\n{wind_send}\n{trigger_cause_send}\n{pedestrian_density_send}\n{traffic_density_send}\n{special_vehicles_send}\n{zones_send}\n{road_types_send}\n{intersections_send}\n{roundabouts_send}\n{special_structures_send}\n"

        for client in self.clients:
            try:
                client.sendall(message.encode())
                self.text_area.insert(tk.END, f"서버에서 보낸 메시지: metadata, routedata 전송 완료\n")
            except Exception as e:
                self.text_area.insert(tk.END, f"메시지 전송 실패: {e}\n")
                self.clients.remove(client)  # 실패한 클라이언트 제거

    def combobox_create(self, items, master_frame, title, w):
        frame = tk.Frame(master_frame)
        frame.pack(side=tk.LEFT, padx=10)
        label = tk.Label(frame, text=title).pack()
        combobox = ttk.Combobox(frame, width=w, values=items, state="readonly")
        combobox.pack(pady=5)
        combobox.bind("<<ComboboxSelected>>", lambda event: self.combobox_update(title, combobox))

    def combobox_update(self, title, combobox):
        self.combobox_value[title] = combobox.get()

    def checkbox_create(self, items, master_frame, title):
        frame = tk.Frame(master_frame)
        frame.pack(side=tk.LEFT, padx=10)
        label = tk.Label(frame, text=title).pack()
        
        self.checkbox_value[title] = {}
        
        for idx, item in enumerate(items):
            var = tk.StringVar(value="")
            checkbox = tk.Checkbutton(frame, text=item, variable=var, onvalue=str(idx), offvalue="")
            checkbox.pack(anchor="w")
            self.checkbox_value[title][item] = var

    def textbox_create(self, master_frame, title, w):
        frame = tk.Frame(master_frame)
        frame.pack(side=tk.LEFT, padx=10)
        label = tk.Label(frame, text=title).pack()
        textbox = tk.Entry(frame, width=w)
        textbox.pack(pady=5)
        self.textbox_value[title] = textbox

if __name__ == "__main__":
    root = tk.Tk()
    root.geometry("650x1000")
    app = ServerApp(root)
    root.mainloop()

