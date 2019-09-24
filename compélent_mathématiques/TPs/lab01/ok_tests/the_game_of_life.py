test = {
  'name': 'the_game_of_life',
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> board = np.array([[0,0,0,0,0,0],
          ...                   [0,0,0,1,0,0],
          ...                   [0,1,0,1,0,0],
          ...                   [0,0,1,1,0,0],
          ...                   [0,0,0,0,0,0],
          ...                   [0,0,0,0,0,0]]);
          >>> 
          >>> count = neighbor_counting(board);
          >>> 
          >>> new_board = evolution_rules(board, count);
          >>> 
          >>> print(new_board)
          e57b2432a7cc115156d66c0225cfdfcf
          62f8f7c2c6539cee6490af51efffe228
          025def58e13ca8023bb47ef94984863d
          8508d278c8d3284a0d3403def6c5abe3
          1fe5e4673cef4c26afb8ddda63bab42c
          e71677337557c59fe2b257d009b4520f
          # locked
          """,
          'hidden': False,
          'locked': True
        }
      ],
      'scored': True,
      'setup': '',
      'teardown': '',
      'type': 'doctest'
    }
  ]
}
