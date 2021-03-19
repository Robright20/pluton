import React, {useState, useEffect} from "react";
import ReactDOM from "react-dom";
import {Pluton, GeneralInfo} from "./pluton";
// import {Pluton} from "./pluton";
import router from "./router";
import {sleep, getLine, say} from "./lib";
import {Proc} from "./models";
import "./style.css";
const log = console.log;
const WS_SERVER = "ws://localhost:3000";
import 'regenerator-runtime/runtime'

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
  const setters = {};
  const height = 896;
  const width = 896;
  const idxMod = 64;
  const scale = width / 64;
  const users = {};
  const procs = {};

  function dispatch(event, ...args) {
    const callbacks = setters[event] || [];

    callbacks.forEach((cb) => {
      cb(...args);
    });
  }

  function saveSetters(event, cb) {
    setters[event] ??= [cb];

    if (setters[event].length !== 1)
      setters[event].push(cb);
  };

  const Draw = function(data) {
    const {ctx, cells} = data;
    const ws = new WebSocket(WS_SERVER);

    ws.addEventListener('open', () => {
      log('[WS] connected.')
    });
    ws.addEventListener('message', async (msg) => {
      let line = getLine(ws, msg.data);

      do {
        if (/^##/.test(line)) {
          dispatch("status", "RUNNING...");
          router.call({
            users,
            procs,
            cells,
            ctx,
            Proc,
            say,
            ws,
            dispatch
          }, line);
        }
        log("[MSG] " + line);
      } while ((line = getLine(ws)));
      // await sleep(100);
      ws.send("ACK\n")
    });
  }

  return (
    <div>
    <Pluton
      startDraw={Draw}
      options={({
        width,
        height,
        scale,
        idxMod
      })}
    />
    <GeneralInfo saveSetter={saveSetters} />
    </div>
  );
}

ReactDOM.render(<Index />, document.getElementById('root'));

/*
    <Warrior saveSetter={saveSetters} />

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