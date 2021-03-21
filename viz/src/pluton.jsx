import React, {useState, useEffect} from "react";
import fakeUsers from "./users.json";
import {map4Obj, say} from "./lib";
import {Cell} from "./models";

function Warrior({user, saveSetter, id}) {
  
  useEffect(() => {
    saveSetter("check", (users) => {
      users[id] ? users[id].lastLives = 0 : false;
    });
  }, [saveSetter]);

  return (
    <div className="Warrior">
        <p><b>Name </b>: {user.info["name"]}</p>
        <p><b>Desc </b>: {user.info["desc"]}</p>
        <p><b>Size </b>: {user.info["size"]}</p>
        <p><b>Procs </b>: {user.procList.length}</p>
        <p><b>Lives Since </b>:</p>
        <li><b>last check :</b> {user.lastLives}</li>
        <li><b>Begining   :</b> {user.lives}</li>
    </div>
  );
}

export function WarriorsBox({saveSetter}) {
  const [users, updateUsers] = useState(fakeUsers);
  Object.defineProperty(users, "_map", {value: map4Obj});

  useEffect(() => {
    saveSetter("users", updateUsers);
  }, [saveSetter]);

  return (
    <div id="WarriorsBox">
      {(
        users._map(([id, user]) => {
          return (<Warrior
            user={user}
            key={id}
            id={id}
            saveSetter={saveSetter}
          />)
        })
      )}
    </div>
  );
}

export function GeneralInfo({saveSetter}) {
  const [cycle, updateCycle] = useState();
  const [cycleToDie, updateCycleToDie] = useState();
  const [status, setStatus] = useState();

  useEffect(() => {
    saveSetter("cycle", updateCycle);
    saveSetter("cycleToDie", updateCycleToDie);
    saveSetter("status", setStatus);
  }, [saveSetter]);

  return (
    <div id="GeneralInfo">
      <b> { cycle == null ? "DEBUT" : status } </b>
        <span><b>CYCLE_TO_DIE </b>: { cycleToDie ?? 1536 }</span>
        <span><b>CYCLE_DELTA </b>: 50</span>
        <span><b>MAX_CHECKS  </b>: 10</span>
        <span><b>NBR_LIVE    </b>: 21</span>
        <span><b> CYCLE </b>: {cycle ?? 0} </span>
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
      cell = new Cell(i, "00");
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
