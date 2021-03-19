import React, {useState, useEffect} from "react";
import {Cell} from "./models";

export function Warrior({saveSetter, id}) {
  const [users, updateUsers] = useState();
  const user = users?.[id] || {};

  useEffect(() => {
    saveSetter("users", updateUsers);
  }, [saveSetter]);

  return (
    <div className="Warrior">
      <p>Name: {user.info["name"]}</p>
      <p>Desc: {user.info["desc"]}</p>
      <p>Size: {user.info["size"]}</p>
      <p>Procs: {user.procList.length}</p>
      <p>Lives Since:</p>
      <ul>
        <li>last check: {user.lastLives}</li>
        <li>game start: {user.lives}</li>
      </ul>
    </div>
  );
}

export function GeneralInfo({saveSetter}) {
  const [cycle, updateCycle] = useState(0);
  const [status, updateStatus] = useState("BEGINING");

  useEffect(() => {
    saveSetter("cycle", updateCycle);
    saveSetter("status", updateStatus);
  }, [saveSetter]);

  return (
    <div id="GeneralInfo">
      <p> {status} </p>
      <p> {cycle} </p>
      <p>
        CYCLE_TO_DIE: 1536<br />
        CYCLE_DELTA : 50<br />
        MAX_CHECKS  : 10<br />
        NBR_LIVE    : 21
      </p>
    </div>
  );
}

export function Pluton({startDraw, options}) {
  useEffect(() => {
    const canvas = document.getElementById('canvas');
    const ctx = canvas.getContext('2d');
    const cells = [];
    let cell;

    Object.assign(ctx, options);
    for (let i = 0; i < 4096; i++) {
      cell = new Cell(i, "2e");
      cell.draw(ctx);
      cells.push(cell);
    }
    startDraw({ctx, cells});
  }, []);

  return (
    <div>
      <canvas
        id="canvas"
        width={options.width}
        height={options.height}
      >
      </canvas>
    </div>
  );
}
