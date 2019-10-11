test = {
  'name': 'uniform_sampling',
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> grid = uniform_sampling(9, 1, 3, 5,10);
          >>> 
          >>> print(grid)
          [[ 1.   5. ]
           [ 2.   5. ]
           [ 3.   5. ]
           [ 1.   7.5]
           [ 2.   7.5]
           [ 3.   7.5]
           [ 1.  10. ]
           [ 2.  10. ]
           [ 3.  10. ]]
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
