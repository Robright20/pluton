import React, {useState} from "react";
import ReactDOM from "react-dom";
import Pluton from "./pluton";
import router from "./router";
import getLine from "./getLine";
import {Cell, User, Proc} from "./models";
import "./style.css";

const log = console.log;
const WS_SERVER = "ws://localhost:3000";

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

function load4UserTest(loadFunc, UserFunc, ctx) {
    let user = new UserFunc("bob", "1337 Student", 300);
    user.procList.push(new Proc(user.id, 0));
    loadFunc(user, ctx, 200);

    user = new UserFunc("bob", "1337 Student", 350);
    user.procList.push(new Proc(user.id, 0));
    loadFunc(user, ctx, 1200);

    user = new UserFunc("bob", "1337 Student", 300);
    user.procList.push(new Proc(user.id, 0));
    loadFunc(user, ctx, 2000);

    user = new UserFunc("bob", "1337 Student", 500);
    user.procList.push(new Proc(user.id, 0));
    loadFunc(user, ctx, 3000);
}

function Index() {
  const height = 896;
  const width = 896;
  const idxMod = 64;
  const scale = width / 64;
  const users = [];

  const Draw = function(data) {
    const {ctx, } = data;
    Object.assign(ctx, {scale, idxMod});
    let cell;
    for (let i = 0; i < 4096; i++) {
      cell = new Cell(i, "2e");
      drawCell(cell, ctx);
    }

    load4UserTest(loadUser, User, ctx);

    const ws = new WebSocket(WS_SERVER);
    ws.addEventListener('open', () => {
      log('[WS] connected.')
    });
    ws.addEventListener('message', msg => {
      let line = getLine(ws, msg.data);

      do {
        if (/^##/.test(line)) {
          router.call({
            users,
            ctx,
            drawCell,
            Cell,
            Proc
          }, line);
        }
      } while ((line = getLine(ws)));
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