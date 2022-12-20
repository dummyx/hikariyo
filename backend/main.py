from fastapi import FastAPI, Response

from settings import SECRET

app = FastAPI(docs_url=None, redoc_url=None, openapi_url=None)

# 222: empty
# 221: switch
command = 222

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
