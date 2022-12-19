from typing import Union

from fastapi import FastAPI, Response

app = FastAPI()

switch = False

@app.get("/light", status_code = 221)
def get_light_status(response: Response):
    response.status_code = 222  if switch else 221
    return {
        "light" : switch
    }

@app.patch("/light")
def flip_light_status():
    global switch 
    switch = not switch
    return None