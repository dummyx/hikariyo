from fastapi import FastAPI, Response

from settings import SECRET, SERVER_URL
from datetime import datetime
from fastapi.middleware.cors import CORSMiddleware

app = FastAPI(docs_url=None, redoc_url=None, openapi_url=None)

origins = [
    SERVER_URL,
    "http://localhost",
    "http://localhost:8080",
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# 222: empty
# 221: switch
command = 222

data: dict[str, list[dict[str, int | str]]] = {
    "data": []
}

is_on = False

LIGHT_THRESHOLD = 2300

# For frontend.
@app.get("/light")
def get_light_status():
    return {
        "light" : is_on
    }

@app.get("/set_on")
def set_on(secret: str):
    if secret != SECRET:
        return None
    global is_on
    is_on = True

@app.get("/set_off")
def set_off(secret: str):
    if secret != SECRET:
        return None
    global is_on
    is_on = False
    
@app.get("/get_command")
def get_command(response: Response):
    global command
    response.status_code = command

    # Clear command.
    command = 222
    
@app.post("/set_command")
def set_command(secret: str):
    if secret != SECRET:
        return None

    global command
    command = 221

@app.get("/upload_data")
def upload(value: int, secret: str):
    if secret != SECRET:
        return None

    global data
    time_string = datetime.now().isoformat()
    data["data"].append({
        "time": time_string,
        "value": value,
    })

@app.get("/get_data")
def get_data():
    global data
    return data

