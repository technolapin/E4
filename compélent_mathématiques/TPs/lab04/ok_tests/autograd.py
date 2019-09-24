test = {
  'name': 'autograd',
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> a = np.array([3., 2, 4, 7]);
          >>> w = np.array([2.,-1, 0, 5, 1]);
          >>> 
          >>> print(function(w, a), gradient(w, a))
          26.0 [1. 3. 2. 4. 7.]
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
