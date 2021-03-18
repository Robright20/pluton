import React, {useState} from "react";
import ReactDOM from "react-dom";
import Pluton from "./pluton";
import router from "./router";
import {getLine, say} from "./lib";
import {Proc} from "./models";
import "./style.css";
const log = console.log;
const WS_SERVER = "ws://localhost:3000";

// instructions

/*

* #new-cycle
* #new-process userId pid pc
* #new-check
* #new-user userId
* #new-data pid idx [data]
* #kill-process pid

*/

function Index() {
  const height = 896;
  const width = 896;
  const idxMod = 64;
  const scale = width / 64;
  const users = {};
  const procs = {};

  const Draw = function(data) {
    const {ctx, cells} = data;

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
            procs,
            cells,
            ctx,
            Proc,
            say
          }, line);
        }
        log("[MSG] " + line)
        ws.send("ACK\n");
      } while ((line = getLine(ws)));
    });
  }

  return (
    <Pluton
      startDraw={Draw}
      options={({
        width,
        height,
        scale,
        idxMod
      })}
    >
    </Pluton>
  );
}

ReactDOM.render(<Index />, document.getElementById('root'));

/*

** RANDOM THOUGHTS
===================

proc[i]
&addr
-3

corewar -n 1 p1.cor 0 p2.cor -n 2 p3.cor

[1][1][1][1]

[1] [filename]
[2] [...]
[4] [...]
[3] [...]

*/