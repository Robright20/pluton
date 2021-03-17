import React, {useState} from 'react';

function Cell(props) {
	[cell, setData] = useState();

	useEffect(() => {
		cell.draw(props.ctx);

		return cell.clear.bind(cell); //bind just to be sure
	}, [cell]);
	return <p id={props.id}>{`cell ${props.id} has changed.`}</p>;
}