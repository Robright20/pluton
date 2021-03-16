import React, {useState} from "react";
import ReactDOM from "react-dom";
import Pluton from "./pluton";
import router from "./router";
import getLine from "./getline";
import middlewares from "./middlewares";
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

function Index() {
  const height = 896;
  const width = 896;
  const idxMod = 64;
  const scale = width / 64;
  const users = {};
  const procs = {};

  const Draw = function(data) {
    const {ctx, } = data;
    Object.assign(ctx, {scale, idxMod});
    let cell;
    for (let i = 0; i < 4096; i++) {
      cell = new Cell(i, "2e");
      cell.draw(ctx);
    }

    const ws = new WebSocket(WS_SERVER);
    ws.addEventListener('open', () => {
      log('[WS] connected.')
    });
    ws.addEventListener('message', msg => {
      let line = getLine(ws, msg.data);

      do {
        if (/^##/.test(line)) {
          router.call({
            middlewares,
            users,
            procs,
            ctx,
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