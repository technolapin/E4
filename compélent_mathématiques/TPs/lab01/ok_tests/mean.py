test = {
  'name': 'mean',
  'points': 3,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> np.round(mean_all, decimals=4)
          4.6667
          """,
          'hidden': False,
          'locked': False
        },
        {
          'code': r"""
          >>> print(np.round(mean_rows, decimals=4))
          [6.75 2.   5.25]
          """,
          'hidden': False,
          'locked': False
        },
        {
          'code': r"""
          >>> print(np.round(mean_cols, decimals=4))
          [3.6667 5.6667 4.     5.3333]
          """,
          'hidden': False,
          'locked': False
        }
      ],
      'scored': True,
      'setup': '',
      'teardown': '',
      'type': 'doctest'
    }
  ]
}
