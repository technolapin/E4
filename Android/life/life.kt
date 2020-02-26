enum class State{On, Off}

 class Grid(val width: Int, val height: Int, val states: List<State>)
{

    constructor(width: Int, height: Int): this(
	width,
	height,
	(1..(width*height)).map{State.Off}.toList()
    )
    
    constructor(old_gr: Grid): this(
	old_gr.width,
	old_gr.height,
	
	(0..(old_gr.width*old_gr.height-1))
	    .map{Pair(it % old_gr.width, it / old_gr.width)}
	    .map{
		val (i, j) = it
		val sum_ngh =
		    listOf(
			Pair(-1, -1),
			Pair(-1,  0),
			Pair(-1,  1),
			Pair( 0,  1),
			Pair( 1,  1),
			Pair( 1,  0),
			Pair( 1, -1),
			Pair( 0, -1))
		    .map{Pair(i+it.first, j+it.second)}
		    .filter{it.first >= 0 && it.first < old_gr.width &&
			    it.second >= 0 && it.second < old_gr.height}
		    .map{old_gr.states[it.first+it.second*old_gr.width]}
		    .filter{it == State.On}
		    .count()
		if (sum_ngh == 3)
		{
		    State.On
		}
		else if (sum_ngh == 2)
		{
		    old_gr.states[it.first+it.second*old_gr.width]
		}
		else
		{
		    State.Off
		}
		
	    }
    )
    
    final fun draw_at(drawing: Map<Pair<Int, Int>, State>, position: Pair<Int, Int>): Grid
    {
	var list = this.states.toMutableList()

	drawing
	    .filterKeys {
		it.first + position.first >= 0 && it.first + position.first < this.width &&
		it.second + position.second >= 0 && it.second + position.second < this.height
	    }
	    .forEach {
		(pos, state) -> list[pos.first + pos.second*this.width] = state
	    }
	

	return Grid(this.width, this.height, list)
    }

    final fun print()
    {
	for (i in 0..(this.width-1))
	{
	    for (j in 0..(this.height-1))
	    {
		when (this.states[i + j*this.width])
		{
		    State.On -> print("O")
		    State.Off -> print("·")
		}
	    }
	    println()
	}
    }
}


fun main(args: Array<String>) {

    val gilder = mapOf(
	Pair(1, 0) to State.On,
	Pair(2, 1) to State.On,
	Pair(2, 2) to State.On,
	Pair(1, 2) to State.On,
	Pair(0, 2) to State.On
    )
    var gr = Grid(8, 8).draw_at(gilder, Pair(1, 1))
    println("Generation 0")
    gr.print()

    for (generation in (1..8))
    {
	gr = Grid(gr)
	println("Generation $generation")
	gr.print()
    }
}
