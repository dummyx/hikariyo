from fastapi import FastAPI, Response

from settings import SECRET
from datetime import datetime

app = FastAPI(docs_url=None, redoc_url=None, openapi_url=None)

# 222: empty
# 221: switch
command = 222

data: dict[str, int] = {}

is_on = False

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
    data[time_string] = value

@app.get("/get_data")
def get_data():
    global data
    return data

