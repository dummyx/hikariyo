from fastapi import FastAPI, Response

app = FastAPI()

switch = False

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
def set_on():
    global is_on
    is_on = True

@app.get("/set_off")
def set_off():
    global is_on
    is_on = False
    
@app.get("/get_command")
def get_command(response: Response):
    global command
    response.status_code = command

    # Clear command.
    command = 222
    
@app.post("/set_command")
def set_command():
    global command
    command = 221
