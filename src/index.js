import React, {useState} from "react";
import ReactDOM from "react-dom";
import Pluton from "./pluton";
import router from "./router";
import "./style.css";
const log = console.log;
const WS_SERVER = "ws://localhost:8080";

// instruction

/*
* #new-cycle
* #new-process userId pid pc
* #new-check
* #new-user userId
* #new-data pid idx [data]
* #kill-process pid

proc[i]
&addr
-3

corewar -n 1 p1.cor 0 p2.cor -n 2 p3.cor

[1][1][1][1]

[1] [filename]
[2] [...]
[4] [...]
[3] [...]

runIf("", cb);

*/


// change canvas.height/width
// get the rendering context canvas.getContext('2d')
const userColor = [
  // "#6fcf97",
  "#00ff69",
  // "#9cffc5",
  "#eb5757",
  "#56ccf2",
  "#f2c94c"
];
const procColor = [
  "#9cffc5",
  // "#00ff69",
  "#ffd0d0",
  "#c8f2ff",
  "#fdeec1"
];
let cuid = 0;
// let cellDefaultBg = "#f7f6f5";
let cellDefaultBg = "grey";
let cellDefaultBorder = "";

function Cell(id, text) {
  this.id = id;
  this.text = {
    value: text,
    fontFamily: "",
    color: "",
    size: 0
  };
  this.bgColor = cellDefaultBg;
  this.border = cellDefaultBorder;
}

function Proc(uid, pid) {
  this.uid = uid;
  this.id = pid;
  this.PC = 0;
  this.info = {
    carry: 0,
    color: procColor[uid],
    lives: 0
  }
}

function User(name, desc, size) {
  this.id = cuid++;
  this.info = {
    name,
    desc,
    size,
    color: userColor[this.id]
  }
  this.procList = [new Proc(this.id, 0)];
}

//(4*1024)
function drawCell(cell, ctx) {
  if (!cell instanceof Cell) {
    return false;
  }
  const x = (cell.id % ctx.idxMod) * ctx.scale;
  const y = Math.floor(cell.id / ctx.idxMod) * ctx.scale;
  ctx.clearRect(x, y, ctx.scale, ctx.scale)
  if (ctx.scale >= 20) {
    ctx.font = `80% serif`;
    ctx.textBaseline = 'top';
    ctx.fillText(cell.text.value, x + 1, y + 1);
  }
  ctx.fillStyle = cell.bgColor;
  ctx.fillRect(x, y, ctx.scale, ctx.scale)
  ctx.strokeStyle = cell.border;
  ctx.lineWidth = cell.lineWidth;
  ctx.strokeRect(x, y, ctx.scale, ctx.scale)
}

function loadUser(user, ctx, position) {
  const proc = user.procList[0];
  let cell;

  proc['info'].PC = 10;
  for (let i = 0; i < user['info'].size; i++) {
      cell = new Cell(position, "2e");
      cell.bgColor = user.['info'].color;
      cell.lineWidth = 1.0;
      if (i == proc['info'].PC) {
        cell.lineWidth = 2.5;
        cell.bgColor = proc['info'].color;
      }
      drawCell(cell, ctx);
      position++;
  }
}
function Index() {
  const height = 896;
  const width = 896;
  const idxMod = 64;
  const scale = width / 64;
  const users = [];
  const dataBak = [];

  const Draw = function(data) {
    const {ctx, } = data;
    Object.assign(ctx, {scale, idxMod});
    let cell;
    for (let i = 0; i < 4096; i++) {
      cell = new Cell(i, "2e");
      drawCell(cell, ctx);
    }
    let user = new User("bob", "1337 Student", 300);
    loadUser(user, ctx, 200);
    user = new User("bob", "1337 Student", 350);
    loadUser(user, ctx, 1200);
    user = new User("bob", "1337 Student", 300);
    loadUser(user, ctx, 2000);
    user = new User("bob", "1337 Student", 500);
    loadUser(user, ctx, 3000);


    const ws = new WebSocket(WS_SERVER);
    ws.addEventListener('open', () => {
      log('[WS] connected.')
    });
    ws.addEventListener('message', data => {
      const line = "";
      dataBak = dataBak.concat(data.split("\n"));
      while ((line = dataBak.shift()))
        router.call({
          users,
          ctx,
          drawCell,
          Cell,
          Proc}, line);
    });
  }

  return (
    <Pluton
      startDraw={Draw}
      canvasWidth={width}
      canvasHeight={height}
    >
    </Pluton>);
}

ReactDOM.render(<Index />, document.getElementById('root'));