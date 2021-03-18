import React, {useState, useEffect} from "react";
import {Cell} from "./models";

function Pluton({startDraw, options}) {
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

export default Pluton;