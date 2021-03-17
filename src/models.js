const Cell = (function() {
  const cellDefaultBg = "grey";
  const cellDefaultBorder = "";

  function drawCell(ctx) {
    const x = (this.id % ctx.idxMod) * ctx.scale;
    const y = Math.floor(this.id / ctx.idxMod) * ctx.scale;
    ctx.clearRect(x, y, ctx.scale, ctx.scale)
    if (ctx.scale >= 20) {
      ctx.font = `80% serif`;
      ctx.textBaseline = 'top';
      ctx.fillText(this.text.value, x + 1, y + 1);
    }
    ctx.fillStyle = this.bgColor;
    ctx.fillRect(x, y, ctx.scale, ctx.scale)
    ctx.strokeStyle = this.border;
    ctx.lineWidth = this.lineWidth;
    ctx.strokeRect(x, y, ctx.scale, ctx.scale)
  }
  return function Cell(id, text) {
    this.id = id;
    this.text = {
      value: text,
      fontFamily: "",
      color: "",
      size: 0
    };
    this.bgColor = cellDefaultBg;
    this.border = cellDefaultBorder;
    this.draw = drawCell;
  }
})();

module.exports = {
  Cell,
  User: (function() {
    let cuid = 0;
    const userColor = [
      "#00ff69",
      "#eb5757",
      "#56ccf2",
      "#f2c94c"
    ];

    function loadUser(ctx, position) {
      const proc = this.procList[0];
      let cell;

      proc['info'].PC ??= position;
      for (let i = 0; i < this['info'].size; i++) {
          cell = new Cell(position, "2e");
          cell.bgColor = this.['info'].color;
          cell.lineWidth = 1.0;
          cell.draw(ctx);
          position++;
      }
    }
    return function(name, desc, code, size) {
      this.id = cuid++;
      this.info = {
        name,
        desc,
        code,
        size,
        color: userColor[this.id]
      };
      this.procList = [];
      this.load = loadUser;
    }
  })(),

  Proc: (function() {
    const procColor = [
      "#9cffc5",
      "#ffd0d0",
      "#c8f2ff",
      "#fdeec1"
    ];

    return function(uid, pid, pc) {
      this.uid = uid;
      this.id = pid;
      this.PC = pc;
      this.info = {
        carry: 0,
        color: procColor[
          (typeof uid === "number") ? uid : uid.id
        ],
        lives: 0
      };
      this.cell = new Cell(pc, "2e");
      this.cell.bgColor = this.['info'].color;
      this.cell.lineWidth = 2.5;
    }
  })()
};