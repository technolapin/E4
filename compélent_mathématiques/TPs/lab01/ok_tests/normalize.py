test = {
  'name': 'normalize',
  'points': 2,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> print(max_values)
          [[9]
           [9]
           [7]]
          """,
          'hidden': False,
          'locked': False
        },
        {
          'code': r"""
          >>> print(np.round(new_matrix, decimals=4))
          [[0.5556 0.8889 1.     0.5556 0.     0.    ]
           [0.1111 0.7778 0.6667 1.     0.2222 0.4444]
           [0.7143 0.2857 0.5714 0.2857 0.5714 1.    ]]
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
