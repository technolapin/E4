test = {
  'name': 'softmax',
  'points': 3,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> print(np.round(s_all, decimals=4))
          11207758a3be5b1fca0713f9da680f0b
          5db27dd0c997e985ec0ef3cff228748e
          # locked
          """,
          'hidden': False,
          'locked': True
        },
        {
          'code': r"""
          >>> print(np.round(s_cols, decimals=4))
          7e46159cd23e9f71b6192f539185aea9
          75c9d6c35639a33a847e3336a4453494
          # locked
          """,
          'hidden': False,
          'locked': True
        },
        {
          'code': r"""
          >>> print(np.round(s_rows, decimals=4))
          440a291c5ad7198e8e3ad048b6505f92
          ba563f5871b68757a6c5063caa8e9d75
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
