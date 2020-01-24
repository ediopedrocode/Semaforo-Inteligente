import json

from flask import Flask, render_template, redirect, request
from flask_socketio import SocketIO, send, emit
from flask_cors import CORS

app = Flask(__name__)
socketio = SocketIO(app)
CORS(app)

estado = {
    "QTD_VIA1" : 0,
    "QTD_VIA2" : 0,
    "ORDEM_VERMELHO" : 0,
    "ORDEM_AMARELO" : 0
    }

@app.route("/")
def rota_inicial():
    print(estado)
    return render_template("index.html")

@app.route("/upload", methods = ["POST"])
def rota_data():
    global estado
    estado = request.get_json()
    socketio.emit("atualiza",estado)
    return "200"

@app.route("/download", methods = ["GET"])
def rota_download():
    global estado
    return json.dumps(estado)

@socketio.on('abrir_pedestres')
def abrir_pedestres():
    global estado
    estado["ORDEM_VERMELHO"] = 1

@socketio.on('fechar_pedestres')
def fechar_pedestres():
    global estado
    estado["ORDEM_VERMELHO"] = 0

@socketio.on('abrir_amarelo')
def abrir_amarelo():
    global estado
    estado["ORDEM_AMARELO"] = 1

@socketio.on('fechar_amarelo')
def fechar_amarelo():
    global estado
    estado["ORDEM_AMARELO"] = 0

if __name__ == "__main__":
    app.run("0.0.0.0",port=8080)